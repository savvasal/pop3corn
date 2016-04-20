#ifndef __THREAD_H__
#define __THREAD_H__

#include "commons.h"
#include "protocol.h"
#include <pthread.h>
#include <signal.h>
#include <unistd.h> 

#define perror2(s, e) fprintf(stderr, "%s:%s\n", s, strerror(e)) 

#define RUNNING 1 
#define WAITING 0

typedef struct {
  int status;
  int socket;
  pthread_t id;
  char users_filename[MAX_STRING];
} thread;

int start_thread(thread *current_thread);

void *runner(void *parameters);

void sighand(int signo);

#endif
