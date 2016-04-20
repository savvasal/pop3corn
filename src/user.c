#include "user.h"


int
is_valid_username(user *current_user, char *username) {

  char temp_username[MAX_USERNAME], temp_password[MAX_PASSWORD];
  FILE *users_file;
  int number_of_users = 0, i=0;

  users_file = fopen(current_user->users_filename, "r");
  fscanf(users_file,"%d",&number_of_users);

  for(i = 0; i<number_of_users; i++) {
    fscanf(users_file,"%s %s",temp_username, temp_password);
    if(strcmp(temp_username,username) == 0) {
      strcpy(current_user->username,temp_username);
      strcpy(current_user->password,temp_password);
      fclose(users_file);
      return SUCCEED;
    }
  }
  
  fclose(users_file);

  return ERROR;	
}

int
is_correct_password(user *current_user, char *temp_password) {
  if(strcmp(current_user->password, temp_password) == 0) {
    return SUCCEED;
  }
  
  return ERROR;
    
}
