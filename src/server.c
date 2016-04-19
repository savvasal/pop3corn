#include "server.h"

int
new_server_socket(int port) {

  int socket_fd = -1;
  unsigned int server_sockaddr_len = 0;
  struct sockaddr *server_sockaddr_ptr = NULL;
  struct sockaddr_in server_sockaddr;
  
  /* CREATE socket for server */
  
  /* definintion http://pubs.opengroup.org/onlinepubs/7908799/xns/socket.html */
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
    perror("socket");
    exit(1);
  }
  
  server_sockaddr.sin_family = AF_INET; /* Internet domain */
  server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* My Internet address */
  server_sockaddr.sin_port = htons(port); /* The given port */
  
  server_sockaddr_ptr = (struct sockaddr *) &server_sockaddr;
  server_sockaddr_len = sizeof server_sockaddr;
  
  /* definition - bind  http://pubs.opengroup.org/onlinepubs/7908799/xns/bind.html */
  if (bind(socket_fd, server_sockaddr_ptr, server_sockaddr_len) < 0) {
    perror("bind");
    exit(1);
  }
  
  /* definition http://pubs.opengroup.org/onlinepubs/7908799/xns/listen.html */
  if (listen(socket_fd, BACKLOG) < 0)   { 
    perror("listen");
    exit(1);
  }
  
  return socket_fd;  
}

int
close_server_socket(int socket) {

  return shutdown(socket, SHUT_RDWR);
    
}

