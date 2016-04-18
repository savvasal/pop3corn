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


// general constants
#define MAX_STRING 128

// STATE Constant values 
#define AUTHORIZATION 0 
#define TRANSACTION   1 
#define UPDATE        2 

#define perror2(s, e) fprintf(stderr, "%s:%s\n", s, strerror(e)) 

#define RUNNING 1 
#define WAITING 0 


//void *runner();

int main(int argc, char *argv[]) /* Server with Internet stream sockets */ 
{
  // general usage variables
  char temp_string[MAX_STRING];
  int i = 0;
  
  // variables for reading configuration file
  FILE *config_file = NULL, *users_file = NULL;
  char config_filename[MAX_STRING], users_filename[MAX_STRING];
  int threads_number = 0, port_number = 0;

  // variables for threads
  int *thread_status = NULL;
  int *thread_socket = NULL;
  // int port, sock, newsock, serverlen, i; 
  // socklen_t clientlen; 
  // char buf[256]; 
  // struct sockaddr_in server, client; 
  // struct sockaddr *serverptr, *clientptr; 
  // struct hostent *rem; 
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
  
  // INITIALIZE common arrays for threads
  thread_status = (int *) malloc(threads_number * sizeof(int));
  if(!thread_status) {
    perror("not enough space");
    exit(1);
  } 
  
  
  thread_socket = (int *) malloc(threads_number * sizeof(int));
  if(!thread_socket) {
    perror("not enough space");
    free(thread_status);
    exit(1);
  }

  for(i=0; i < threads_number; i++) {
    thread_status[i] = WAITING;
    thread_socket[i] = -1;
  }

  
  // close files - free memory
  // TODO clean up in case of exit earlier
  // TODO check for every exit above
  free(thread_status);
  free(thread_socket);
  fclose(users_file);
}

