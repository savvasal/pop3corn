#ifndef __POOL_H__
#define __POLL_H__

#include "commons.h"
#include "thread.h"

#define MAX_THREADS 100

typedef struct {
  int number_of_threads;
  thread threads[MAX_THREADS];
} pool;


/* take as argument number of threads and return pool */
int new_pool_of_threads(pool *pool_of_threads, int number_of_threads, char *users_filename);

int start_threads(pool *pool_of_threads);

int get_available_thread(pool *pool_of_threads);

/* int assign_thread_to_client(pool pool_of_threads); */

#endif
