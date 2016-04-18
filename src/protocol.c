#include "protocol.h"

int initializeProtocol(char *users_filename) {
  
  users_file = fopen(users_filename, "r");
  
  return 1;
}


void respondToCommand(int *state, char *command, char *return_value){
  
  char *save, *token;
  
  token = strtok_r(command, " ", &save);
  
  if (token==NULL){ 
    printf("token = NULL\n");
    sprintf(return_value,"-ERR Invalid Command");
    return;
    
  }
  else
    switch((*state)) {
      
    case AUTHORIZATION:
      
      if (strcmp(token,"QUIT")==0) {
        // sign off
        // ...
	sprintf(return_value, "+OK %s POP3 server signing off", username);
        return;
        
      }
      
      else if (strcmp(token,"USER")==0){
	
        token = strtok_r(NULL, " ", &save);
	
        if (token==NULL){
          // Error: Username wasn't given
          username = NULL;
	  sprintf(return_value,"-ERR ...");
          return;
        }

	else if (isValidUsername(token)) {
          return ("+OK %s is a valid mailbox", username);
	  sprintf(return_value,"-ERR ...");
          return;
        }
	else {   
          username = NULL;
          return ("-ERR never heard of mailbox %s",token);
        }
                        
      }
      
      else if (strcmp(token,"PASS")==0) { 
        token = strtok_r(NULL, " ", &save);
	
        if (username==NULL){ 
          return "-ERR username not given"; // or sth else ?
        }
	else if (token != NULL && isCorrectPassword(token)){
          // anoigw to mailbox
          // ...
          // Change state to TRANSACTION - AUTHORIZATION is over
          (*state) = TRANSACTION;
          return "+OK maildrop locked and ready";
        }
	else { 
          username = NULL;
	  password = NULL;
          return ("-ERR invalid password");
        }
                        
      }
      else {
        // Invalid command for this state     
	username = NULL;
        return "-ERR invalid command for AUTHORIZATION";
      } 
      break; // End of AUTHORIZATION state commands
    }
  
}

int isValidUsername(char *username) {

  char temp_username[MAX_USERNAME], temp_password[MAX_PASSWORD];
  
  while(fscanf(users_file,"%s %s",temp_username, temp_password)) {
    if(strcmp(temp_username,username) == 0) {
      strcpy(username,temp_username);
      strcpy(password,temp_password);
      return TRUE;
    }
  }
  return FALSE;
	
}

int isCorrectPassword(char *temp_password) {
  if(strcmp(password, temp_password) == 0)
    return TRUE;
  
  return FALSE:
    
}
