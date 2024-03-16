/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:36:43 by ndahib            #+#    #+#             */
/*   Updated: 2024/03/16 13:28:58 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* ************************************************************************** */
/*			ORHTODOX CANNINICAL FORM : Client								  */
/* ************************************************************************** */

Client::Client() : id(-1)
{
		
}
Client::Client(int id, bool isWriteEvent, struct sockaddr_in &clientAdr): id(id), isWriteEvent(isWriteEvent), clientAddr(clientAdr)
{
	//nothin here
}

Client::Client(const Client &client)
{
	(void)client;
}

Client::~Client()
{
	//TODO[]remove that 
	// if (id != -1)
	// 	close(id);
}

Client Client::operator=(const Client &client)
{
	if (this != &client)
	{
		memcpy(this->buffer, client.buffer, BUFFER_SIZE);
		this->id = client.id;
		this->isWriteEvent = client.isWriteEvent;
		this->clientAddr = client.clientAddr;
	}
	return (*this);
}

void 	Client::set_idd(int fd)
{
	this->id = fd;
}

void 	Client::set_issWriteEvent(bool opt)
{
	isWriteEvent = opt;
}

void 	Client::set_clientAddr(struct sockaddr_in &clientAddr)
{
	this->clientAddr = clientAddr;
}

int		Client::get_id() const
{
	return (id);
}

bool 	Client::is_write_event() const
{
	return (isWriteEvent);
}

struct sockaddr_in	Client::get_client_addr() const 
{
	return (clientAddr);
}