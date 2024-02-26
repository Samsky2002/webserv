# include "webserv.hpp"

Config::Config()
{

}

Config::Config(const Config & config)
{
	*this = config;
}

Config & Config::operator=(const Config & config)
{
	if ( this != &config )
	{
		this->serverConfig = config.serverConfig;
		this->config_file = config.config_file;
	}
	return ( *this );
}

Config::~Config()
{

}

void Config::setup( const std::string & file )
{
	// here we parse and we handle config
	(void)file;
	ServerConfig serverConfig1;
	ServerConfig serverConfig2;
	Location location1;
	
	location1.path = "/";
	location1.root = "/Users/oakerkao/Desktop/nginx/html/";
	location1.methods.push_back( "GET" );
	location1.autoindex = false;
	//location1.index = "index.html";
	serverConfig1.port = 800;
	serverConfig1.host = "127.0.0.1";
	serverConfig1.server_name = "oussama";
	serverConfig1.error_pages.push_back( std::make_pair( 400, "/error" ) );
	serverConfig1.client_body_size = 100;
	serverConfig1.location.push_back( location1 );
	serverConfig2.port = 801;
	serverConfig2.host = "127.0.0.1";
	serverConfig2.server_name = "oussama2";
	serverConfig2.error_pages.push_back( std::make_pair( 400, "/error" ) );
	serverConfig2.client_body_size = 100;
	serverConfig2.location.push_back( location1 );
	// final_push
	serverConfig.push_back( serverConfig1 );
	serverConfig.push_back( serverConfig2 );
}
