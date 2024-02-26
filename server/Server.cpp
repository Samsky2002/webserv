#include "webserv.hpp"

Server::Server()
{

}


Server & Server::operator=( const Server & server )
{
	if ( this != &server )
	{

	}
	return ( *this );
}

Server::~Server()
{

}

void Server::setup(const Config & config)
{
	size_t i = 0;

	while ( i < config.serverConfig.size() )
	{
		serverInfo.push_back( ServerInfo( config.serverConfig[i] ) );
		i++;
	}
}
