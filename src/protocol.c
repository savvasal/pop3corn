#include "protocol.h"

int
new_protocol(protocol *current_protocol, char *users_filename) {

  user current_user;
  current_protocol->state = AUTHORIZATION;
  strcpy(current_user.users_filename, users_filename);
  current_protocol->current_user = current_user;
  
  return SUCCEED;
}

int
respond_to_command(protocol *my_protocol, char *command, char *return_value) {

  char *save, *token;
  char temp_string[MAX_STRING];
  token = strtok_r(command, " ", &save);

  // First time to be called for the specific request
  // Make state from UPDATE to AUTHORIZATION
  if (my_protocol->state == UPDATE)
    strcpy(my_protocol->state, AUTHORIZATION);
	
  if (token==NULL){ 
    strcpy(return_value,"-ERR Invalid Command");
    return ERROR;
		
  } else switch(my_protocol->state) {
    case AUTHORIZATION:
      if (strcmp(token,"QUIT")==0) {
        // sign off
        // ...
	sprintf(temp_string, "+OK %s POP3 server signing off", protocol->current_user.username);
	strcpy(return_value, temp_string);
        return QUIT;
   
      } else if (strcmp(token,"USER")==0){
        token = strtok_r(NULL, " ", &save);
        if (token==NULL){
          protocol->current_user.username = NULL;
	  strcpy(return_value,"-ERR username wasn't given");
          return ERROR;
		  
        } else if (is_valid_username(&(protocol->current_user), token)) {
          sprintf(temp_string, "+OK %s is a valid mailbox", protocol->current_user.username);		  
	  strcpy(return_value,temp_string);
          return SUCCEED;
		  
        } else {   
          protocol->current_user.username = NULL;
          sprintf(temp_string, "-ERR never heard of mailbox %s", token);		
	  strcpy(return_value,temp_string);
          return ERROR;
        }
 
      } else if (strcmp(token,"PASS")==0){ 
        token = strtok_r(NULL, " ", &save);
        if (protocol->current_user.username==NULL){ 
	  strcpy(return_value,"-ERR username wasn't given");
          return ERROR;
		  
        } else if (token != NULL && is_correct_password(&(protocol->current_user), token)){
          // do i have to save the password?
          // anoigw to mailbox
          // ...
          // Change state to TRANSACTION - AUTHORIZATION is over
	  strcpy(my_protocol->state, TRANSACTION);
	  strcpy(return_value,"+OK maildrop locked and ready");
          return SUCCEED;
		  
        } else { 
          protocol->current_user.username = NULL;
	  strcpy(return_value,"-ERR invalid password";
		 return ERROR;
		 }
                        
	} else {
	  // Invalid command for this state     
	  protocol->current_user.username = NULL;
	  strcpy(return_value,"-ERR invalid command for AUTHORIZATION");
	  return ERROR;
	} 
	break; // End of AUTHORIZATION state commands
        
      case TRANSACTION:
	if (strcmp(token,"QUIT")==0) {
	  // Apeleutherwse porous
	  // quit thread
	  // ...
	  // Change state to UPDATE
	  strcpy(my_protocol->state, UPDATE);
	  strcpy(return_value,"+OK Quit");
	  return QUIT;
      
	} else if (strcmp(token,"STAT")==0){
	  int numOfMessages;   // Number of messages in mailbox  - not the deleted ones
	  int sizeOfMailbox;   // Total size of mailbox in bytes - not the deleted ones
	  // Calculate the two numbers asked (could be counted while reading...)
	  // ...
	  sprintf(temp_string, "+OK %d %d", numOfMessages, sizeOfMailbox);		
	  strcpy(return_value,temp_string);
	  return SUCCEED;
  
	} else if (strcmp(token,"LIST")==0){
	  token = strtok_r(NULL, " ", &save);
	  if (token==NULL){
	    // Multiple line response
	    char *response;
	    // > If no messages in mailbox => +OK
	    // > Otherwise
	    // +OK x messages (x octets)
	    // For each message: x y
	    // x: number of message
	    // y: size of messages in bytes
	    // ...
	    strcpy(return_value,response); // TODO multiple line response
	    return SUCCEED;

	  } else {
	    // token is the number of message
	    if (message_exists(token)) {
	      if (is_deleted(token)){
		sprintf(temp_string, "-ERR message %s is deleted", token);		
		strcpy(return_value,temp_string);
		return ERROR;
			  
	      } else {
		// Calculate size of message in bytes
		// ... 
		sprintf(temp_string, "+OK %s %d", token, sizeInBytes);		
		strcpy(return_value,temp_string);
		return SUCCEED;
			  
	      }
	    } else {
	      sprintf(temp_string, "-ERR no such message, only %d messages in mailbox", numOfMessages);		
	      strcpy(return_value,temp_string);
	      return ERROR;
	    }
	  }
                        
	} else if (strcmp(token,"RETR")==0){
	  token = strtok_r(NULL, " ", &save);
	  if (token==NULL){
	    strcpy(return_value,"-ERR Invalid command");
	    return ERROR;
		  
	  } else if (message_exists(token)) {
	    if (is_deleted(token)){
	      sprintf(temp_string, "-ERR message %s is deleted", token);		
	      strcpy(return_value,temp_string);
	      return ERROR;
			
	    } else {
	      // calculate size, read message & return these two values
	      char *response;
	      // "+OK %d octets", sizeInBytes;
	      // messageData
	      // "."
	      strcpy(return_value,response); // TODO multiple line response
	      return SUCCEED;
	    }
	  } else {
	    strcpy(return_value,"-ERR no such message");
	    return ERROR;
	  }                        
                        
	} else if (strcmp(token,"DELE")==0){
	  token = strtok_r(NULL, " ", &save);
	  if (token==NULL){
	    strcpy(return_value,"-ERR Invalid command");
	    return ERROR;
		  
	  } else if (message_exists(token)) {
	    if (is_deleted(token)){
	      sprintf(temp_string, "-ERR message %s is already deleted", token);		
	      strcpy(return_value,temp_string);
	      return ERROR;
			  
	    } else {
	      make_deleted(token);
	      sprintf(temp_string, "+OK message %s deleted", token);
	      strcpy(return_value,temp_string);
	      return SUCCEED;
			
	    }
	  } else {
            strcpy(return_value,"-ERR no such message");
	    return ERROR;
	  }

	} else {
	  // Invalid command for this state
	  strcpy(return_value,"-ERR invalid command for TRANSACTION");
	  return ERROR;
	} 
	break; // End of TRANSACTION state commands
      } // End of switch
    }
