#ifndef HTTP_HPP
# define HTTP_HPP
# include <vector>
# include "Config.hpp"
# include "Server.hpp"

class Http
{
	public:
		Config config;
		Server server;
		std::string config_file;
		Http();
		Http( const Http & http );
		Http & operator=( const Http & http );
		~Http();
		void setup(const std::string & file);
		void launch();
};

#endif
