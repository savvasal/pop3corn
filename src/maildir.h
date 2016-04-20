#ifndef __MAILDIR_H__
#define __MAILDIR_H__

#include "commons.h"
#include "user.h"

typedef struct {
  char *directory;
} maildir;

int open_maildir(user *current_user);

#endif
