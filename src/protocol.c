#include "protocol.h"

int
new_protocol(protocol *current_protocol, char *users_filename) {

  user current_user;
  current_protocol->state = UPDATE;
  strcpy(current_user.users_filename, users_filename);
  current_protocol->current_user = current_user;
  
  return SUCCEED;
}

int
respond_to_command(protocol *current_protocol, char *command, char *return_value) {

  char *save, *token;

  token = strtok_r(command, " ", &save);
  
  if(current_protocol->state == UPDATE) {
    strcpy(return_value, "+OK POP3 server ready\r\n");
    current_protocol->state = AUTHORIZATION;
  }
  else if(token) {
    
    if ( strcmp(token,"USER") == 0  && current_protocol->state == AUTHORIZATION) {
      token = strtok_r(NULL, " ", &save);
      if(is_valid_username(&(current_protocol->current_user), token) == SUCCEED)
	strcpy(return_value, "+OK Nice username. Give PASS your password\r\n");
      else
	strcpy(return_value, "-ERR I don't know you\r\n");
    }
    else if ( strcmp(token,"PASS") == 0 && current_protocol->state == AUTHORIZATION) {
      token = strtok_r(NULL, " ", &save);
      if(is_correct_password(&(current_protocol->current_user), token) == SUCCEED) {
	strcpy(return_value, "+OK WOW. Correct password. Let's go to transaction\r\n");  
	current_protocol->state = TRANSACTION;
      }
      else
	strcpy(return_value, "-ERR Oops wrong password. Try again\r\n");
    }
    else if ( strcmp(token,"QUIT") == 0) {
      strcpy(return_value, "+OK You want to leave. Bye Bye. Go to update.\r\n");  
      current_protocol->state = UPDATE;
      return QUIT;
    }
    else if ( strcmp(token,"STAT") == 0 && current_protocol->state == TRANSACTION)
      strcpy(return_value, "+OK STAT not implemented\r\n");  

    else if (strcmp(token,"DELE") == 0 && current_protocol->state == TRANSACTION)
      strcpy(return_value, "+OK DELE not implemented\r\n");  
  
    else if (strcmp(token,"LIST") == 0 && current_protocol->state == TRANSACTION)
      strcpy(return_value, "+OK LIST not implemented\r\n");  

    else if (strcmp(token,"RETR") == 0 && current_protocol->state == TRANSACTION )
      strcpy(return_value, "+OK LIST not implemented\r\n");
  
    else
      strcpy(return_value, "-ERR I don't understand you\r\n");
  }
  return SUCCEED;
}

