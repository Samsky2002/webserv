#include "webserv.hpp"

ServerInfo::ServerInfo() {}

// we can add some file called tools for the function helper like the_inet_addr()
// this function is implemnted with getaddrinfo that store the informations of address in struct 
// i thinks it is good bcs hnadle a lost of cases that my bitoize operation not good for it;
in_addr_t	ft_inet_addr(const char *ipAddrString, int family, int type)
{
	struct addrinfo hints, *addrInfo;
	in_addr_t		s_addr;

	memset(&hints, 0, sizeof(addrinfo));
	hints.ai_family = family;
	hints.ai_socktype = type;
	hints.ai_protocol = IPPROTO_TCP;

	if (getaddrinfo(ipAddrString, NULL, &hints, &addrInfo) != 0)
	{
		std::cerr << "Error in getInfo of Adress " << std::endl;
		freeaddrinfo(addrInfo);
		return (-1);
	}
	s_addr = ((struct sockaddr_in *)addrInfo->ai_addr)->sin_addr.s_addr;
	freeaddrinfo(addrInfo);
	return (s_addr);
}

bool	ServerInfo::matchServer(int id) const
{
	return (listener == id);
}

bool	ServerInfo::is_Client_exist(int fdClient) const
{
	for (size_t i = 0; i < Client.size(); i++)
	{
		if (Client[i].get_id() == fdClient)
			return (true);
	}
	return(false);
}

ServerInfo::ServerInfo( const ServerConfig & serverConfig )
{
	this->host = serverConfig.host;

	this->port = serverConfig.port;
	std::cout << "[" << port << "]" << std::endl;
	this->family = AF_INET;
	this->addrLen = sizeof( struct sockaddr );
	memset(&serverAddr, '\0', sizeof( struct sockaddr ));
	this->serverAddr.sin_family = this->family;
	this->serverAddr.sin_port = htons( this->port );
	this->type = SOCK_STREAM;
	// this->serverAddr.sin_addr.s_addr = ft_inet_addr("10.12.3.6", this->family, this->type);
	// this->serverAddr.sin_addr.s_addr = ft_inet_addr(host.c_str(), family, type);
	this->serverAddr.sin_addr.s_addr = INADDR_ANY;
	this->domain = PF_INET;
	this->protocol = 0;
	this->level = SOL_SOCKET;
	this->option_name = SO_REUSEADDR;
	this->option_value = 1;
	this->option_len = sizeof( option_value ); 
	this->backlog = 20;

	// to be continued
}

ServerInfo::ServerInfo( const ServerInfo & serverInfo )
{
	*this = serverInfo;
}

ServerInfo & ServerInfo::operator=( const ServerInfo & serverInfo )
{
	if ( this != &serverInfo )
	{
		this->host = serverInfo.host;
		this->port = serverInfo.port;
		this->family = serverInfo.family;
		this->serverAddr = serverInfo.serverAddr;
		this->clientAddr = serverInfo.clientAddr;
		this->addrLen = serverInfo.addrLen;
		this->domain = serverInfo.domain;
		this->type = serverInfo.type;
		this->protocol = serverInfo.protocol;
		this->listener = serverInfo.listener;
		this->level = serverInfo.level;
		this->option_name = serverInfo.option_name;
		this->option_value = serverInfo.option_value;
		this->option_len = serverInfo.option_len;
		this->backlog = serverInfo.backlog;
		this->Client = serverInfo.Client;
	}
	return ( *this );
}

ServerInfo::~ServerInfo() {}

void	guard(int returnValue, int listner, std::string msg)
{
	if (returnValue == -1)
	{
		std::cerr << msg << strerror(errno) << std::endl;
		close(listner);
		throw(1);
	}
}

void	ServerInfo::launch()
{
	try{
				//create socket;
		listener = socket(domain, type, protocol);
		guard(listener, listener,  "Faillue on creating Socket ");

				//customizing socket ;
		// guard(setsockopt(listener, level, option_name, &option_value, option_len), listener, "Faillue on customizing  Socket " );

		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &option_value, option_len);
		setsockopt(listener, SOL_SOCKET, SO_REUSEPORT, &option_value, option_len);

		int current_flag = fcntl(listener, F_GETFL);
		if (current_flag == -1)
		{
			std::cout << " error in fcntl get flag "<< std::endl;
			exit(1);
		}
		if (fcntl(listener , F_SETFL, current_flag | O_NONBLOCK) == -1)
		{
			perror ("error in setting non_block flag ");
			exit(1);
		}

				//biding socket ;
		guard(bind(listener, (const sockaddr *) &serverAddr, addrLen), listener, "Faillue on binding Socket " );

				//listening to upcoming conection
		guard(listen(listener, backlog), listener,  "Faillue on Listening " );

		//add somte features like non Socketint and option to socket
		std::cout << "We got the server " << listener << "that have the adreess " << this->host 
		<< " and the Port " << this->port << std::endl;

	}catch(int number)
	{
		close(listener);
		std::cout << "Stoping Server ..." << std::endl;
	}
}
