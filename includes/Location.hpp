#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <vector>
# include <iostream>

class Location
{
	public:
		std::string path;
		std::vector<std::string> methods;
		std::string redirection;
		std::string root;
		bool autoindex;
		std::vector<std::string> index;
		std::string upload;
		std::string cgi;

		// list of accepted routes
		// redirection
		// root directory => to look for
		// directory listing
		// default file to answer
		Location();
		Location(const Location & location);
		Location & operator=(const Location & location);
		~Location();
};

#endif
