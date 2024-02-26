#ifndef CONFIG_HPP
# define CONFIG_HPP
# include "ServerConfig.hpp"

class Config
{
	public:
		std::vector<ServerConfig> serverConfig;
		std::string config_file;
		Config();
		Config(const Config & config);
		Config & operator=(const Config & config);
		~Config();
		void setup( const std::string & file );
};

#endif
