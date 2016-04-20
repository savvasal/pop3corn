#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "commons.h"
#include <fcntl.h>

typedef struct {
  char *directory_path;
  int id; // start from 1
  int size_of_message; // octet
} message;

// int new_message(char *filename);
// lock file - return

// unlock file 
#endif
