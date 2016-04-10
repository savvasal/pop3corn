#include <sys/types.h> /* For sockets */
#include <sys/socket.h> /* For sockets */
#include <netinet/in.h> /* For Internet sockets */
#include <netdb.h> /* For gethostbyname */
#include <stdio.h> /* For I/O */
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

//imap send function

// pernei parametro thn entolh pou tha steilei

// th stelnei panw apo to socket


// pianei thn apanthsh kai thn epistrefei

int main(int argc, char *argv[]) {
  
  int port, sock, serverlen; char buf[256];
  struct sockaddr_in server;
  struct sockaddr *serverptr;
  struct hostent *rem;
  int i;

  
  if (argc < 3)
    { /* Check if server's host name and port number are given */
      printf("Please give the host name and the port number\n");
      exit(1);
    }
  
  return 0;
}



 
