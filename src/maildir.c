#include "maildir.h"


// http://pubs.opengroup.org/onlinepubs/009695399/functions/fcntl.html
int new_message(char *filename) {
  /*  int fd;
      struct flock fl;
  
  
      fd = open("testfile", O_RDWR);
      if (fd == -1)
      perror("fd");
  
      fl.l_type = F_WRLCK;
      if (fcntl(fd, F_SETLK, &fl) == -1) {
      if (errno == EACCES || errno == EAGAIN) {
      printf("Already locked by another process\n");
      } else { */
  
  /* Handle unexpected error */;
  // }
  //  } else { /* Lock was granted... */


  /* Perform I/O on bytes 100 to 109 of file */


  /* Unlock the locked bytes */


  //   fl.l_type = F_UNLCK;
  //   if (fcntl(fd, F_SETLK, &fl) == -1)
  /* Handle error */;
  //}
  // exit(EXIT_SUCCESS);

  return 0;
}


int
open_maildir(user *current_user) {
    
  
  return 0;
}
