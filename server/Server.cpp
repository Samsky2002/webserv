#include "webserv.hpp"

Server::Server()
{
	std::cout << "this is Constructor of Server" << std::endl;
}


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
	// until this moment don't have any role
	// but later maybe
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


void	Server::launch_server(size_t i)
{
	ServerInfo	serverSocket = serverInfo.at(i);

	//create socket;
	serverSocket.listener = socket(serverSocket.domain, serverSocket.type, serverSocket.protocol);
	if (serverSocket.listener == -1){
		std::cerr << "Faillue on creating Socket " << i << strerror(errno) << std::endl;
		return ;
	}

	//Customizing the socket befor binding
	if (setsockopt(serverSocket.listener, serverSocket.level, serverSocket.option_name, &serverSocket.option_value, serverSocket.option_len) == -1){
		std::cerr << "Faillue on customizing  Socket " << i << strerror(errno) << std::endl;
		return ;		
	}

	if (fcntl(serverSocket.listener, F_SETFL, O_NONBLOCK) == -1){
		std::cerr << "Faillue while seting the socket non_blocking: " << i << strerror(errno) << std::endl;
		return ;		
	}

	//bind
	if (bind(serverSocket.listener, (const sockaddr *) &serverSocket.serverAddr, serverSocket.addrLen) == -1){
		std::cerr << "Faillue on binding Socket " << i << strerror(errno) << std::endl;
		return ;		
	}

	//listen
	if (listen(serverSocket.listener, serverSocket.backlog) == -1){
		std::cerr << "Faillue on Listening " << i << strerror(errno) << std::endl;
		return ;		
	}

	//add somte features like non Socketint and option to socket
}

void	Server::launch()
{
	for (size_t i = 0; i < serverInfo.size(); i++)
	{
		this->launch_server(i);
	}
}
