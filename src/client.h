#ifndef __POOL_H__
#define __POLL_H__

#include "commons.h"
#include <sys/socket.h> // For sockets 
#include <netinet/in.h> // For Internet sockets 

int accept_client(int server_socket);


#endif
