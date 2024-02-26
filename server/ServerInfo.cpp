#include "webserv.hpp"

ServerInfo::ServerInfo()
{
	
}

ServerInfo::ServerInfo( const ServerConfig & serverConfig )
{
	this->host = serverConfig.host;
	this->port = serverConfig.port;
	this->family = AF_INET;
	this->addrLen = sizeof( struct sockaddr );
	memset(&serverAddr, '\0', sizeof( struct sockaddr ));
	this->serverAddr.sin_family = this->family;
	this->serverAddr.sin_port = htons( port );
	this->serverAddr.sin_addr.s_addr = INADDR_ANY;
	this->domain = PF_INET;
	this->type = SOCK_STREAM;
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
