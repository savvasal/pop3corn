#include "thread.h"


int
start_thread(thread *current_thread) {
  int err = 0;

  err = (pthread_create(&(current_thread->id), NULL, &runner,(void *) current_thread));
  if (err) {
    perror2("pthread_create", err);
    return ERROR;
  }

  return SUCCEED;

}


void *runner(void *parameters){
  char buffer[MAX_BUFFER]; //, return_value[MAX_STRING];
  char response_buffer[MAX_BUFFER];
  thread *my_info = (thread *) parameters;
  signal(SIGALRM, sighand);
  protocol my_protocol;
  int resp = 0;
  while (true) {
    my_info->status = WAITING;
    if(my_info->status != RUNNING)
      pause();
    my_info->status = RUNNING;
    
    new_protocol(&my_protocol, my_info->users_filename);
    bzero(response_buffer, sizeof response_buffer);
    bzero(buffer, sizeof buffer);
    respond_to_command(&my_protocol, buffer, response_buffer);
    bzero(buffer, sizeof buffer);
    sprintf(buffer, response_buffer);
    
    if (write(my_info->socket, buffer, sizeof buffer) < 0) {
      perror("write");
      exit(1);
    }    
    
    do {
      //  READ command from the client and print it
      bzero(buffer, sizeof buffer); /* Initialize buffer */
      if (read(my_info->socket, buffer, sizeof buffer) < 0) { /* Receive message */
	perror("read");
	exit(1);
      }
      
      // EXECUTE AND GENERATE answer
      bzero(response_buffer, sizeof response_buffer);
      resp = respond_to_command(&my_protocol, buffer, response_buffer);
      
      // SEND answer to client
      bzero(buffer, sizeof buffer);
      sprintf(buffer, response_buffer);
      if (write(my_info->socket, buffer, sizeof buffer) < 0) { /* Send message */
	perror("write");
	exit(1);
      }
    } while(resp != QUIT);
  }  
  
}


void sighand(int signo) {
  
}

