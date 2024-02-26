#ifndef SERVER_HPP
# define SERVER_HPP
# include "ServerInfo.hpp"

class Server
{
	public:
		std::vector<ServerInfo> serverInfo;
		Server();
		Server & operator=(const Server & server);
		~Server();
		void setup(const Config & config);
};

#endif
