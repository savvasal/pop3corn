#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "commons.h"
#include "user.h"

#define AUTHORIZATION 0
#define TRANSACTION 1
#define UPDATE 2

#define QUIT -2
typedef struct {
  int state;
  user current_user;
} protocol;


int new_protocol(protocol *current_protocol, char *users_filename);

int respond_to_command(protocol *my_protocol, char *command, char *return_value);

#endif
