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

int
get_available_thread(pool *pool_of_threads) {
  int i = 0;

  for(i=0; i < pool_of_threads->number_of_threads; i++)
    if((pool_of_threads->threads[i]).status == WAITING)
      return i;

  return ERROR;

}
