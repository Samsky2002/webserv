#ifndef HTTP_HPP
# define HTTP_HPP
# include <vector>
# include "Config.hpp"
# include "Server.hpp"
# include "Multiplexing.hpp"

class	Http
{
	private:
		Config		config;
		Server		server;
		std::string	configFile;
		Multiplexing	multiplexer;

	public:
		Http();
		Http( const Http & http );
		Http & operator=( const Http & http );
		~Http();
		void setup(const std::string & file);
		void launch();
};

#endif
