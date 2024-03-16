#include "webserv.hpp"

Server::Server() {}


Server & Server::operator=( const Server & server )
{
	if ( this != &server )
	{
		this->serverInfo = server.serverInfo;
	}
	return ( *this );
}

Server::~Server()
{
	// close the socket if the server finish his work;
}

void	Server::setup(const Config & config)
{
	size_t i = 0;

	while ( i < config.serverConfig.size() )
	{
		serverInfo.push_back( ServerInfo( config.serverConfig[i] ) );
		i++;
	}
}

void	Server::launch()
{
	for (size_t i = 0; i < serverInfo.size(); i++)
	{
		serverInfo[i].launch();
	}
}
