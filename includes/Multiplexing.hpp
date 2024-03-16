# ifndef MULTIPLEXING_HPP
# define MULTIPLEXING_HPP

#include "webserv.hpp"
#include "Client.hpp"
// struct	s_event
// {
// 	int fd_event;
// 	void (*ReadHandler)(s_event *obj);
// 	void (*WriteHandler)(s_event *obj);
// };

class	Multiplexing
{
	private:
		int 						kq;
		int 						quit;
		int 						nevents;
		int 						nlisteners;
		Server 						server;
		struct timespec 			timeout;
		struct kevent				Changeevent;
		std::vector<int> 			listeners;
		std::vector<struct kevent> 	readEvents;
		std::vector<struct kevent> 	writeEvents;
	
		void	add_lisetner(int listener);
		void	add_client(Client &new_client, int &fdServer);
		void	add_event();
		void	delet_listener(int listener);
		void	delete_client(int client);
		void	delete_event();
		void	accepting(int &fdServer);

	public:
		Multiplexing();
		~Multiplexing();
		void	launch();
		void	setup(Server &server);
		int sk;
		class KQUEUE_EXCEPTION : public std::exception
		{
			const char *what() const _NOEXCEPT { return ("Faillure on creating kernel queue :") ;};
		};
		class KEVENT_EXCEPTION : public std::exception
		{
			const char *what() const _NOEXCEPT { return ("Faillure in kevent :") ;};
		};
};

#endif /*MULTIPLEXING_HPP*/