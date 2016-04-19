#include "commons.h"
#include "server.h"

int
main(int argc, char *argv[]) {

  char temp_string[MAX_STRING];

  FILE *config_file = NULL, *users_file = NULL;
  char config_filename[MAX_STRING], users_filename[MAX_STRING];  

  int threads_number = 0, port_number = 0;
  int socket_fd = -1;
  //, new_socket_fd = -1;  /* fd stands for file descriptor */
  
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

  
  
  socket_fd = new_server_socket(port_number);

  close_server_socket(socket_fd);
  // dhmiourghse threads

  // ksekina threads
  
  
  // listener
  //do {


  // client new socket  =

  // assign to a thread if is available otherwise - 

    
  //} while(true); //ctrl+c or a signal
  
  
  
  // close files - free memory
  // TODO clean up in case of exit earlier
  // TODO check for every exit above

  return 0;
}

