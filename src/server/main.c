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

#include "util.h"

// STATE Constant values 
#define AUTHORIZATION 0 
#define TRANSACTION   1 
#define UPDATE        2 

#define perror2(s, e) fprintf(stderr, "%s:%s\n", s, strerror(e)) 
#define THREADS 5 

#define RUNNING 1 
#define WAITING 0 

//void *runner();

int main(int argc, char *argv[]) /* Server with Internet stream sockets */ 
{ 
  int port, sock, newsock, serverlen, i; 
  socklen_t clientlen; 
  char buf[256]; 
  struct sockaddr_in server, client; 
  struct sockaddr *serverptr, *clientptr; 
  struct hostent *rem; 
  pthread_t tid[THREADS]; //threads table 
  int thread_status[THREADS]; 
  int socket_to_client[THREADS]; 
  int number_of_threads = 0;
  FILE *config_file;
  char temp[20];
  char users_file_name[20];
  FILE *users_file;
  
  // read parameters from file
  config_file = fopen("config.txt", "r");
  if(!config_file) {
    perror("Please define parameters at config.txt"); 
    exit(1); 
  }
  
  // read file assume that configuration file has a specific stucture
  number_of_threads = getNumberOfThreads(config_file);
  port = getPortNumber(config_file);
  users_file = getUsersFileName(config_file);
  
  
  fclose(config_file);
  
  // Initialize threads' status
  
  fclose(users_file);
}
