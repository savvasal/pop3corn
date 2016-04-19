#include "user.h"


int
is_valid_username(user *current_user, char *username) {

  char temp_username[MAX_USERNAME], temp_password[MAX_PASSWORD];
  
  while(fscanf(current_user->users_filename,"%s %s",temp_username, temp_password)) {
    if(strcmp(temp_username,username) == 0) {
      strcpy(username,temp_username);
      strcpy(password,temp_password);
      return SUCCEED;
    }
  }
  return ERROR;
	
}

int
is_correct_password(user *current_user, char *temp_password) {
  if(strcmp(current_user->password, temp_password) == 0) {
    return SUCCEED;
  }
  
  return ERROR;
    
}
