/* File: int_str_server.c */
#include <sys/types.h> // For sockets
#include <sys/socket.h> // For sockets
#include <netinet/in.h> // For Internet sockets
#include <netdb.h> // For gethostbyaddr
#include <stdio.h> // For I/O
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void display(int sock);

int main(int argc, char *argv[]) /* Server with Internet stream sockets */
{
  int port, sock, newsock, serverlen;//, clientlen;
  socklen_t clientlen;
  char buf[256];
  struct sockaddr_in server, client;
  struct sockaddr *serverptr, *clientptr;
  struct hostent *rem;
  float amount;


  if (argc < 2)
    { /* Check if server's port number is given */
      printf("Please give the port number\n");
      exit(1);
    }

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { /* Create socket */
      perror("socket");
      exit(1);
    }

  port = atoi(argv[1]); /* Convert port number to integer */
  server.sin_family = AF_INET; /* Internet domain */
  server.sin_addr.s_addr = htonl(INADDR_ANY); /* My Internet address */
  server.sin_port = htons(port); /* The given port */
  serverptr = (struct sockaddr *) &server;
  serverlen = sizeof server;

  if (bind(sock, serverptr, serverlen) < 0)
    { /* Bind socket to an address */
      perror("bind");
      exit(1);
    }
  if (listen(sock, 5) < 0)
    { /* Listen for connections */
      perror("listen");
      exit(1);
    }

  printf("Listening for connections to port %d\n", port);

  while(1)
    {
      clientptr = (struct sockaddr *) &client;
      clientlen = sizeof client;
      if ((newsock = accept(sock, clientptr, &clientlen)) < 0)
        {
	  perror("accept");
	  exit(1);
        } /* Accept connection */

      rem = gethostbyaddr((char *) &client.sin_addr.s_addr, sizeof client.sin_addr.s_addr, /* Find client's address */client.sin_family);
      if (rem == NULL)
        {
	  perror("gethostbyaddr");
	  exit(1);
        }

      printf("Accepted connection from %s\n", rem -> h_name);

      switch (fork())
	{ /* Create child for serving the client */
	case -1:
	  {
	    perror("fork");
	    exit(1);
	  }
	case 0: /* Child process */
	  {
	    display(newsock);
	    // do {
	    //  bzero(buf, sizeof buf); /* Initialize buffer */
	    // if (read(newsock, buf, sizeof buf) < 0)
	    //{ /* Receive message */
	    //	  perror("read");
	    //	  exit(1);
	    //	}
	    //  printf("Read string: %s\n", buf);
	    //  amount = convert(buf); /* Reverse message */
	      
	    //  bzero(buf, sizeof buf);

	    // if (1)
	    //      	{
	    //	  sprintf(buf, "Kalosorises sto katasthma mas");
	    //	  if (write(newsock, buf, sizeof buf) < 0)
	    //	    {  /* Send message */
	    //	      perror("write");
	    //	      exit(1);
	    //	    }
	    //	}
	    //else
	    //	{ 
	    //	  if (write(newsock, country_code, sizeof country_code) < 0)
	    //	    { /* Send message */
	    //	      perror("write");
	    //	      exit(1);
	    //	    }
	    //	}
	    //} while (1); /* Finish on "end" */
	  }
	  close(newsock); /* Close socket */
	  printf("Connection from %s is closed\n", rem -> h_name);
	  exit(0);
        }
    }

  return 0;
}


void display(int sock)
{
  int i;
  char * space = "\t\t";
  char * new_line = "\n"; 
  char buf[20];

  write(sock, "Kalosorises\n", sizeof buf);//country_table[i]);
  read(sock, buf, sizeof buf);   

}
