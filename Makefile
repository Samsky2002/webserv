CPP = c++

CPPFLAGS =  -Wall -Werror -Wextra -std=c++98 -g -fsanitize=address

CLIENT = Client/Client.cpp

MULTIPLEXING = Multiplexing/Multiplexing.cpp

SERVER = server/Server.cpp \
		 server/ServerInfo.cpp

HTTP = http/Http.cpp

CONFIG = config/Config.cpp \
		 config/ServerConfig.cpp \
		 config/Location.cpp \

INCLUDES = -Iincludes/   

CPPFILES = webserv.cpp \
		   $(HTTP) \
		   $(CONFIG) \
		   $(SERVER) \
		   $(MULTIPLEXING)\
		   $(CLIENT)

OBJECTS = $(CPPFILES:.cpp=.o)

NAME = webserv

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CPP) $(CPPFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)

%.o : %.cpp
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
