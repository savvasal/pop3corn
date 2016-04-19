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
  thread *my_info = (thread *) parameters;
  
  signal(SIGALRM, sighand);
  
  while (true) {
    printf("Hello world. I'm thread number %u and ready to serve any client.\n",(unsigned int) pthread_self());
    my_info->status = WAITING;
    // free and clear protocol
    if(my_info->status != RUNNING)
      pause();
    my_info->status = RUNNING;
    // new protocol
    // do
    //  READ command from the client and print it
    bzero(buffer, sizeof buffer); /* Initialize buffer */
    if (read(my_info->socket, buffer, sizeof buffer) < 0) { /* Receive message */
      perror("read");
      exit(1);
    }
    printf("Read string: %s\n", buffer);

    // EXECUTE AND GENERATE answer
    // ret_val = respond_to_command(buf); /* Reverse message */

    // SEND answer to client
    bzero(buffer, sizeof buffer);
    sprintf(buffer, "Welcome");
    if (write(my_info->socket, buffer, sizeof buffer) < 0) { /* Send message */
      perror("write");
      exit(1);
    }
    // while not quit    
  }  
  
}


void sighand(int signo) {

}

