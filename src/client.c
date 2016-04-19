#include "client.h"

int
accept_client(int server_socket) {

  int client_socket_fd = -1;
  unsigned int client_sockaddr_len = 0;
  struct sockaddr *client_sockaddr_ptr = NULL;
  struct sockaddr_in client_sockaddr;
  
  client_sockaddr_ptr = (struct sockaddr *) &client_sockaddr;
  client_sockaddr_len = (socklen_t) sizeof client_sockaddr;
  if ((client_socket_fd = accept(server_socket, client_sockaddr_ptr, &client_sockaddr_len)) < 0)
    {
      perror("accept");
      return ERROR;
    } /* Accept connection */
  
  return client_socket_fd;
}

int
close_client_socket(int socket) {

  return shutdown(socket, SHUT_RDWR);
    
}
