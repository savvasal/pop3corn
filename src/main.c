#include "commons.h"
#include "server.h"
#include "pool.h"
#include "client.h"

int assign_client_to_thread(pool *pool_of_threads, int socket, int thread_id);

int
main(int argc, char *argv[]) {

  char temp_string[MAX_STRING];

  FILE *config_file = NULL, *users_file = NULL;
  char config_filename[MAX_STRING], users_filename[MAX_STRING];  

  int threads_number = 0, port_number = 0;
  int socket_fd = -1, new_socket_fd = -1;
  int available_thread_id = -1;
  
  pool pool_of_threads;
  
  
  /* CHECK server parameters */
  if(argc < 2) {
    printf("Usage is: ./bin/server <configuration file>\n"); 
    exit(1); 
  }

  /* READ configuration file */
  strcpy(config_filename, argv[1]);
  config_file = fopen(config_filename, "r");
  if(!config_file) {
    perror("please give a config file"); 
    exit(1); 
  }
  
  /* ASSUME that configuration file has a specific stucture */
  fscanf(config_file, "%s %d", temp_string, &threads_number);
  fscanf(config_file, "%s %d", temp_string, &port_number);
  fscanf(config_file, "%s %s", temp_string, users_filename);
  
  fclose(config_file);
  
  /* Check if users filename exists and is readable */
  users_file = fopen(users_filename, "r");
  if(!users_file) {
    perror("please give users filename");
    exit(1);
  }
  fclose(users_file);


  /* start server and create socket */
  socket_fd = new_server_socket(port_number);

  /* create threads */
  if( new_pool_of_threads(&pool_of_threads, threads_number, users_filename) == ERROR) {
    perror("create pool of threads");
    exit(1);
  }

  /* start threads */
  if( start_threads(&pool_of_threads) == ERROR ) {
    perror("start threads");
    exit(1);
  }
    
  do {

    new_socket_fd = accept_client(socket_fd);
    
    if( new_socket_fd  == ERROR ) {
      perror("new socket");
      exit(1);
    }
    
    printf("%d\n",(int) new_socket_fd);  

    /* assign to a thread if is available otherwise -  */
    if( (available_thread_id = get_available_thread(&pool_of_threads)) != ERROR)
      assign_client_to_thread(&pool_of_threads, new_socket_fd, available_thread_id);
    else
      close_client_socket(new_socket_fd);
      
  } while(true); //ctrl+c or a signal
  
  
  
  close_server_socket(socket_fd);

  return 0;
}



int
assign_client_to_thread(pool *pool_of_threads, int socket, int thread_id) {

  (pool_of_threads->threads[thread_id]).socket = socket;
  (pool_of_threads->threads[thread_id]).status = RUNNING;  
  pthread_kill(pool_of_threads->threads[thread_id].id, SIGALRM);

  return ERROR;
}



  
