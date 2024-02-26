#include "webserv.hpp"

Location::Location()
{
	methods.push_back("GET");
}

Location::Location(const Location & location)
{
	*this = location;
}

Location & Location::operator=(const Location & location)
{
	if ( this != &location )
	{
		this->path = location.path;
		this->methods = location.methods;
		this->redirection = location.redirection;
		this->root = location.root;
		this->autoindex = location.autoindex;
		this->index = location.index;
	}
	return (*this);
}

Location::~Location()
{

}
