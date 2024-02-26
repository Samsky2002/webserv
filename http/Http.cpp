#include "Http.hpp"

Http::Http()
{

}

Http::Http( const Http & http )
{
	*this = http;
}

Http & Http::operator=( const Http & http )
{
	if ( this != &http )
	{
		this->config = http.config;	
		this->server = http.server;
		this->config_file = http.config_file;
	}
	return ( *this );
}

Http::~Http()
{

}

void Http::setup(const std::string & file)
{
	config.setup( file );
	server.setup( config );	
}
