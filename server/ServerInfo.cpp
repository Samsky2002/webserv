#include "webserv.hpp"

ServerInfo::ServerInfo()
{
	
}

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

ServerInfo::ServerInfo( const ServerConfig & serverConfig )
{
	this->host = serverConfig.host;

	this->port = serverConfig.port;
	this->family = AF_INET;
	this->addrLen = sizeof( struct sockaddr );
	memset(&serverAddr, '\0', sizeof( struct sockaddr ));
	this->serverAddr.sin_family = this->family;
	this->serverAddr.sin_port = htons( this->port );
	this->type = SOCK_STREAM;
	// this->serverAddr.sin_addr.s_addr = ft_inet_addr("10.12.3.6", this->family, this->type);
	this->serverAddr.sin_addr.s_addr = inet_addr(this->host.c_str());
	this->domain = PF_INET;
	this->protocol = 0;
	this->level = SOL_SOCKET;
	this->option_name = SO_REUSEADDR;
	this->option_value = 1;
	this->option_len = sizeof( int );
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
	}
	return ( *this );
}

ServerInfo::~ServerInfo()
{

}
