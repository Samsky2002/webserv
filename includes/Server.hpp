#ifndef	SERVER_HPP
# define SERVER_HPP
# include "ServerInfo.hpp"

class	Server
{
	private:
		std::vector<ServerInfo> serverInfo;

	public:
		Server();
		Server & operator=(const Server & server);
		~Server();
		void	setup(const Config & config);
		void	launch();
		void	launch_server(size_t i);
};

#endif


//README!
/* comments : I changed the the variable from public to private
*/