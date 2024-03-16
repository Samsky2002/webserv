/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndahib <ndahib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:33:51 by ndahib            #+#    #+#             */
/*   Updated: 2024/03/16 13:22:34 by ndahib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CLIENT_HPP
# define CLIENT_HPP

const int BUFFER_SIZE = 1024;

class   Client
{
	private:
		int					id;
		bool				isWriteEvent;
		char 				buffer[BUFFER_SIZE];
		struct sockaddr_in	clientAddr;

	public:    
		Client();
		Client(int id, bool isWriteEvent, struct sockaddr_in &clientAdr);
		Client(const Client &client);
		Client operator=(const Client &client);
		~Client();

		void 	set_idd(int fd);
		void 	set_issWriteEvent(bool opt);
		void 	set_clientAddr(struct sockaddr_in &clientAddr);
		int		get_id() const;
		bool 	is_write_event() const;
		struct sockaddr_in		get_client_addr() const ;
};

#endif
