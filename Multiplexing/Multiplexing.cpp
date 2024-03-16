/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexing.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:37:36 by ndahib            #+#    #+#             */
/*   Updated: 2024/03/16 14:54:50 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	handle_request(int *socket_for_accept)
{
	char	buffer[1050];

	memset(buffer, 0, sizeof(buffer));
	printf("before sending ...\n");
	const char* response = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
	send(*socket_for_accept, response, strlen(response), 0);
	printf("after sending ...\n");
}
void	read_request(int fd)
{
	char	buffer[1050];
	memset(buffer, 0, sizeof(buffer));
	int nbr_bytes = recv(fd, buffer, sizeof(buffer), 0);
	if (nbr_bytes == -1)
	{
		std::cout << "Error receiving data\n" << std::endl;
		//TODO[]close(file descriptor);
		//remove the client from the server;
		//dele all data of this client
	}
	printf("[The Request from Browser] : %s\n", buffer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
Multiplexing::Multiplexing() : nlisteners(0)
{
	quit = false;
	timeout.tv_sec = 5;
	timeout.tv_nsec = 0;
	kq = kqueue();
	if (kq == -1)
		throw(Multiplexing::KQUEUE_EXCEPTION());
}

Multiplexing::~Multiplexing()
{
	close(kq);
}

void	Multiplexing::add_lisetner(int listener)
{
	EV_SET(&Changeevent, listener, EVFILT_READ, EV_ADD, 0, 0, NULL);
	readEvents.push_back(Changeevent);
	nlisteners++;
	listeners.push_back(listener);
	
	if (kevent(kq, readEvents.data(), readEvents.size(), NULL, 0, NULL) == -1)
		throw(Multiplexing::KEVENT_EXCEPTION());
}

void	Multiplexing::setup(Server &server)
{
	this->server = server;
	for (size_t i = 0; i < server.serverInfo.size(); i++)
	{	
		add_lisetner(server.serverInfo[i].listener);
	}
}

void	Multiplexing::delete_client(int fd)
{
	std::cout << "the client disconnected" << std::endl;
	struct kevent Client[2];
	EV_SET(&Client[0], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	EV_SET(&Client[1], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	kevent(kq ,Client ,2, NULL, 0, NULL);
	//#TODO[]// erase from set of the server[i];
	close(fd);
}

void	Multiplexing::add_client(Client &new_client, int &fdServer)
{
	std::vector<ServerInfo> VirtualHosts = server.serverInfo;
	for (size_t i = 0;i < VirtualHosts.size(); i++)
	{
		if (VirtualHosts[i].matchServer(fdServer) && (VirtualHosts[i].is_Client_exist(new_client.get_id() == false)))
		{
			std::cout << "enter here to add the client" << new_client.get_id() << "to the server" << VirtualHosts[i].listener << std::endl; 
			VirtualHosts[i].Client.push_back(new_client);
			return;
		}
	}
}

void	Multiplexing::accepting(int &fd)
{
	std::cout << "Enter here1" << std::endl;
	struct sockaddr_in	his_addr;
	socklen_t size = sizeof(struct sockaddr);
	int new_client = accept(fd, (struct sockaddr *) &his_addr, &size);
	if (new_client == -1)
	{
		perror("error in accepting new_connection ");
		exit(1);
	}
	Client client(new_client, false, his_addr);
	add_client(client, fd);
	std::cout << "the server got connection from " << inet_ntoa(his_addr.sin_addr) << std::endl;
	EV_SET(&Changeevent, new_client, EVFILT_READ, EV_ADD, 0, 0, NULL);
	if (kevent(kq, &Changeevent, 1, NULL, 0, NULL) == -1)
		throw(Multiplexing::KEVENT_EXCEPTION());
}

void	Multiplexing::launch()
{
	try
	{
		struct kevent signaledEvents[20];
		while (!quit)
		{
			int nevents = kevent(kq, NULL, 0,signaledEvents, 20, NULL);
			for (int i = 0; i < nevents; i++)
			{
				int fd = signaledEvents[i].ident;
				std::vector<int >::iterator it;
				// if ident == server_fd then accept new_connection and push the id of the client in vector and set to the Changeevent;
				if ((it = std::find(listeners.begin(), listeners.end(), fd)) != listeners.end())
				{
					accepting(fd);
				}
				// else if client disconnect remove the client from the vector and delete the event from the queue;
				else if (signaledEvents[i].flags & EV_EOF)
				{
					delete_client(fd);
				}
				//else if the client already connected read the request;
				else if (signaledEvents[i].filter == EVFILT_READ)
				{
					//read data and add request to the serveur that connected with this client;
					// and add the client to the write-event;
					read_request(fd);
					EV_SET(&Changeevent, fd, EVFILT_WRITE, EV_ADD | EV_CLEAR, 0, 0, NULL);
					if (kevent(kq, &Changeevent, 1, NULL, 0, NULL) == -1)
						throw(Multiplexing::KEVENT_EXCEPTION());
				}
				//else if the request already sent ; send the response.
				else if (signaledEvents[i].filter == EVFILT_WRITE)
				{
					//find wich client and wich server that should send response;
					std::cout << "=============== WRITE HANDLER ==================" << std::endl;
					handle_request(&fd);
					EV_SET(&Changeevent, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
					kevent(kq, &Changeevent, 1, NULL, 0, NULL);
				}
			}
		}
	}
	catch( std::exception &e)
	{
		close(kq);
		std::cout << e.what() << std::endl;
	}
}