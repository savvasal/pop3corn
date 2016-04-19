#include "pool.h"

int 
new_pool_of_threads(pool *pool_of_threads, int number_of_threads, char *users_filename) {

  int i;
  
  pool_of_threads->number_of_threads = number_of_threads;
  
  
  for(i=0; i < pool_of_threads->number_of_threads; i++) {
    pool_of_threads->threads[i].status = WAITING;
    pool_of_threads->threads[i].socket = -1;
    pool_of_threads->threads[i].users_filename = users_filename;
  }

  return SUCCEED;
}

int
start_threads(pool *pool_of_threads) {
  int i = 0;
  for (i=0; i < pool_of_threads->number_of_threads; i++) {
    if(start_thread(&(pool_of_threads->threads[i])) == ERROR)
      return ERROR;
  }
  return  SUCCEED;
}

/* int getAvailableThread(int threads_number, ThreadInfo *thread_info_array) { */
/*   int i = 0; */
/*   ThreadInfo *thread_info = (ThreadInfo *) thread_info_array; */

/*   for(i=0; i<threads_number; i++) { */
/*     if(thread_info[i].status == WAITING) */
/*       return i; */
/*   } */
  
/*   return -1; */
/* } */

/* int assignClientToThread() { */

  
/*   available_thread_id = getAvailableThread(threads_number, thread_info_array); */
/*   if(available_thread_id != -1) { */
/*     thread_info_array[available_thread_id].socket = new_socket_fd; */
/*     thread_info_array[available_thread_id].status = new_socket_fd; */
/*     pthread_kill(thread_id[available_thread_id], SIGALRM); */
/*   } */
/* } */
