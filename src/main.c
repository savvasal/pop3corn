/* File: int_str_server.c */ 
#include <sys/types.h> // For sockets 
#include <sys/socket.h> // For sockets 
#include <netinet/in.h> // For Internet sockets 
#include <netdb.h> // For gethostbyaddr 
#include <stdio.h> // For I/O 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h> 
#include <pthread.h> 
#include <signal.h>

// general constants
#define MAX_STRING 128
#define true 1
#define false 0
#define MAX_BUFFER 128

// STATE Constant values 
#define AUTHORIZATION 0 
#define TRANSACTION   1 
#define UPDATE        2 

#define perror2(s, e) fprintf(stderr, "%s:%s\n", s, strerror(e)) 

#define RUNNING 1 
#define WAITING 0 

typedef struct {
  int status;
  int socket;
} ThreadInfo;

void *runner(void *parameters);
void sighand(int signo);

// PARAMETERS: number of threads, array of threads' info
// RETURN: id of available thread, otherwhise -1
int getAvailableThread(int threads_number, ThreadInfo *thread_info_array);

//void signalCallbackHandler(int signum, int *stop_flag);

int main(int argc, char *argv[]) {
  
  // general usage variables
  char temp_string[MAX_STRING];
  int i = 0, err=0, available_thread_id = -1;
  
  // variables for reading configuration file
  FILE *config_file = NULL, *users_file = NULL;
  char config_filename[MAX_STRING], users_filename[MAX_STRING];
  int threads_number = 0, port_number = 0;


  // sockets and server variables
  int socket_fd = -1, new_socket_fd = -1;
  unsigned int server_sockaddr_len = 0, client_sockaddr_len = 0;
  struct sockaddr_in server_sockaddr, client_sockaddr; 
  struct sockaddr *server_sockaddr_ptr, *client_sockaddr_ptr;
  

  // auxiliary threads array
  ThreadInfo *thread_info_array = NULL;

  // array for threads
  pthread_t *thread_id = NULL;

  // signal handlers
  // int *stop_flag = false;
  // signal(SIGINT, signalCallbackHandler);
  // int port, sock, newsock, serverlen, i; 
  // socklen_t clientlen; 
  // char buf[256]; 
  // struct sockaddr *serverptr, *clientptr;
  //    struct sockaddr_in server,clint; 

  struct hostent *rem; 
  // pthread_t tid[THREADS]; //threads table 
  // int thread_status[THREADS]; 
  // int socket_to_client[THREADS]; 
  //char temp[20];
  //char users_file_name[20];
  // FILE *users_file;
  
  // read parameters from file
  if(argc < 2) {
    printf("Usage is: ./bin/server <configuration file>\n"); 
    exit(1); 
  }



  // READ configuration file
  strcpy(config_filename, argv[1]);
  config_file = fopen(config_filename, "r");
  if(!config_file) {
    perror("Please give as argument a configuration file"); 
    exit(1); 
  }
  
  //  ASSUME that configuration file has a specific stucture
  fscanf(config_file, "%s %d", temp_string, &threads_number);
  fscanf(config_file, "%s %d", temp_string, &port_number);
  fscanf(config_file, "%s %s", temp_string, users_filename);
  
  fclose(config_file);
  
  // ASSUME that users file has a specific stucture
  users_file = fopen(users_filename, "r");
  if(!users_file) {
    perror("Please initialize a file with users and passwords");
    exit(1);
  }


  // CREATE socket for server
  
  // function definition http://pubs.opengroup.org/onlinepubs/7908799/xns/socket.html
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { /* Create socket */
      perror("socket");
      exit(1);
    }

  // initialize server socket
  server_sockaddr.sin_family = AF_INET; /* Internet domain */
  server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY); /* My Internet address */
  server_sockaddr.sin_port = htons(port_number); /* The given port */

  server_sockaddr_ptr = (struct sockaddr *) &server_sockaddr;
  server_sockaddr_len = sizeof server_sockaddr;

  // function definition of bind  http://pubs.opengroup.org/onlinepubs/7908799/xns/bind.html
  if (bind(socket_fd, server_sockaddr_ptr, server_sockaddr_len) < 0)
    { /* Bind socket to an address */
      perror("bind");
      exit(1);
    }

  // function definition http://pubs.opengroup.org/onlinepubs/7908799/xns/listen.html
  if (listen(socket_fd, threads_number) < 0)
    { /* Listen for connections */
      perror("listen");
      exit(1);
    }

  printf("Listening for connections to port %d\n", port_number);

  // INITIALIZE and malloc threads info array

  thread_info_array = (ThreadInfo *) malloc (threads_number * sizeof(ThreadInfo)); 
  if(!thread_info_array) {
    perror("not enough memory for thread info array");
    exit(1);
  } 
    
  thread_id = (pthread_t *) malloc(threads_number * sizeof(pthread_t));
  if(!thread_id) {
    perror("not enough memory for threads allocation");
    free(thread_info_array);
    exit(1);    
  }
  
  for(i=0; i < threads_number; i++) {
    thread_info_array[i].status = WAITING;
    thread_info_array[i].socket = -1;
  }

  // CREATE threads
  
  for (i=0; i<threads_number; i++) {
    err = (pthread_create(&thread_id[i], NULL, &runner,(void *) &thread_info_array[i]));
    if (err) {
      perror2("pthread_create", err);
      exit(1);
    }
  }

  // listener
  do {
    
    client_sockaddr_ptr = (struct sockaddr *) &client_sockaddr;
    client_sockaddr_len = (socklen_t) sizeof client_sockaddr;
    if ((new_socket_fd = accept(socket_fd, client_sockaddr_ptr, &client_sockaddr_len)) < 0)
      {
	perror("accept");
	exit(1);
      } /* Accept connection */
    
    rem = gethostbyaddr((char *) &client_sockaddr.sin_addr.s_addr, sizeof client_sockaddr.sin_addr.s_addr, /* Find client's address */client_sockaddr.sin_family);
    if (rem == NULL)
      {
	perror("gethostbyaddr");
	exit(1);
      }
    printf("Accepted connection from %s\n", rem -> h_name);

    available_thread_id = getAvailableThread(threads_number, thread_info_array);
    if(available_thread_id != -1) {
      thread_info_array[available_thread_id].socket = new_socket_fd;
      thread_info_array[available_thread_id].status = new_socket_fd;
      pthread_kill(thread_id[available_thread_id], SIGALRM);
    }
    
  } while(true); //ctrl+c or a signal
  
  
  
  // close files - free memory
  // TODO clean up in case of exit earlier
  // TODO check for every exit above
  free(thread_info_array);
  fclose(users_file);
}

void *runner(void *parameters){
  char buffer[MAX_BUFFER]; //, return_value[MAX_STRING];
  ThreadInfo *my_info = (ThreadInfo *) parameters;
  
  signal(SIGALRM, sighand);
  
  while (true) {
    printf("Hello world. I'm thread number %u and ready to serve any client.\n",(unsigned int) pthread_self());
    my_info->status = WAITING;
    if(my_info->status != RUNNING)
      pause();
    my_info->status = RUNNING;
    
    //  READ command from the client and print it
    bzero(buffer, sizeof buffer); /* Initialize buffer */
    if (read(my_info->socket, buffer, sizeof buffer) < 0) { /* Receive message */
      perror("read");
      exit(1);
    }
    printf("Read string: %s\n", buffer);
    
    // read message from client
    // ret_val = respond_to_command(buf); /* Reverse message */
  
    bzero(buffer, sizeof buffer);
    sprintf(buffer, "Welcome");
    if (write(my_info->socket, buffer, sizeof buffer) < 0) { /* Send message */
      perror("write");
      exit(1);
    }
  
    my_info->status = WAITING;
    
  }
  
  
}


void sighand(int signo) {

}




int getAvailableThread(int threads_number, ThreadInfo *thread_info_array) {
  int i = 0;
  ThreadInfo *thread_info = (ThreadInfo *) thread_info_array;

  for(i=0; i<threads_number; i++) {
    if(thread_info[i].status == WAITING)
      return i;
  }
  
  return -1;
}


//void signalCallbackHandler(int signum, int *stop_flag) {
//  *stop_flag = true;
//}
