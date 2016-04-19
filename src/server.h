#ifndef __SERVER_H__
#define __SERVER_H__


#include "commons.h"
#include <sys/socket.h> // For sockets 
#include <netinet/in.h> // For Internet sockets 

#define BACKLOG 5

/* server init_server(); */

int new_server_socket(int port);

int close_server_socket(int socket);


#endif
