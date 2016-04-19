#ifndef __USER_H__
#define __USER_H__

#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 20
#define MAX_PASSWORD 20


typedef struct {
  char username[MAX_USERNAME];
  char password[MAX_PASSWORD];
  char *users_filename; 
} user;



int is_valid_username(user *current_user, char *username);

int is_correct_password(user *current_user, char *temp_password);



#endif
