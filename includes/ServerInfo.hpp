#ifndef SERVERINFO_HPP
# define SERVERINFO_HPP
# include <arpa/inet.h> 

class ServerInfo
{
	public:
		// server name, still don't know it's purpose
		// for sockaddr_in
		std::string host;
		int port;
		int family;
		struct sockaddr_in serverAddr;
		struct sockaddr_in clientAddr;
		socklen_t addrLen;
		// for socket
		int domain;
		int type;
		int protocol;
		int listener;
		// for setsockopt
		int level;
		int option_name;
		int option_value;
		socklen_t option_len;
		// for listen 
		int backlog;
		ServerInfo();
		ServerInfo( const ServerConfig & serverConfig );
		ServerInfo( const ServerInfo & serverInfo );
		ServerInfo & operator=( const ServerInfo & serverInfo );
		~ServerInfo();
};

#endif
