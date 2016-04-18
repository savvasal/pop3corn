char *respond_to_command(int *state, char *command){
	// First time to be called for the specific request
	// Make state from UPDATE to AUTHORIZATION
	if ((*state)==UPDATE)
		(*state) = AUTHORIZATION;
	
	char *save, *tok = strtok_r(command, " ", &save);
	if (tok==NULL){ 
		printf("tok = NULL\n");
		return ("-ERR Invalid Command");
					
	} else switch((*state)) {
    case AUTHORIZATION:
      if (strcmp(tok,"QUIT")==0) {
        // sign off
        // ...
        return ("+OK %s POP3 server signing off", username);
                        
      } else if (strcmp(tok,"USER")==0){
        tok = strtok_r(NULL, " ", &save);
        if (tok==NULL){
          // Error: Username wasn't given
          username = NULL;
          return ("-ERR ...");
        } else if (isValidUsername(tok)) {
          username=tok;
          return ("+OK %s is a valid mailbox", username);
        } else {   
          username = NULL;
          return ("-ERR never heard of mailbox %s",tok);
        }
                        
      } else if (strcmp(tok,"PASS")==0){ 
        tok = strtok_r(NULL, " ", &save);
        if (username==NULL){ 
          return "-ERR username not given"; // or sth else ?
        } else if (tok != NULL && isCorrectPassword(tok)){
          // do i have to save the password?
          // anoigw to mailbox
          // ...
          // Change state to TRANSACTION - AUTHORIZATION is over
          (*state) = TRANSACTION;
          return "+OK maildrop locked and ready";
        } else { 
          username = NULL;
          return ("-ERR invalid password");
        }
                        
      } else {
        // Invalid command for this state     
          username = NULL;
        return "-ERR invalid command for AUTHORIZATION";
      } 
      break; // End of AUTHORIZATION state commands
        
    case TRANSACTION:
      if (strcmp(tok,"QUIT")==0) {
		    // Apeleutherwse porous
		    // quit thread
		    // ...
        // Change state to UPDATE
		    (*state) = UPDATE;
        return ("+OK Quit - Unknown answer to be sent!");
                        
      } else if (strcmp(tok,"STAT")==0){
        int numOfMessages;   // Number of messages in mailbox  - not the deleted ones
        int sizeOfMailbox; // Total size of mailbox in bytes - not the deleted ones
        // Calculate the two numbers asked (could be counted while reading...)
        // ...
        return ("+OK %d %d", numOfMessages, sizeOfMailbox);
                        
      } else if (strcmp(tok,"LIST")==0){
        tok = strtok_r(NULL, " ", &save);
        if (tok==NULL){
          // Multiple line response
          char *response;
          // > If no messages in mailbox => +OK
          // > Otherwise
          // +OK x messages (x octets)
          // For each message: x y
          // x: number of message
          // y: size of messages in bytes
          // ...
          return (response);

        } else {
          // tok is the number of message
          if (messageExists(tok)) {
            if (isDeleted(tok)){
              return ("-ERR message %s is deleted", tok); // or sth like that
            } else {
              // Calculate size of message in bytes
              // ... 
              return ("+OK %s %d", tok, sizeInBytes);
            }
          } else {
            return ("-ERR no such message, only %d messages in mailbox", numOfMessages);
          }
        }
                        
      } else if (strcmp(tok,"RETR")==0){
        tok = strtok_r(NULL, " ", &save);
        if (tok==NULL){
          return ("-ERR Invalid command");
        } else if (messageExists(tok)) {
          if (isDeleted(tok)){
            return ("-ERR message %s is deleted", tok);
          } else {
            // calculate size, read message & return these two values
            char *response;
            // "+OK %d octets", sizeInBytes;
            // messageData
            // "."
            return (response);
          }
        } else {
          return ("-ERR no such message");
        }                        
                        
      } else if (strcmp(tok,"DELE")==0){
        tok = strtok_r(NULL, " ", &save);
        if (tok==NULL){
          return ("-ERR Invalid command");
        } else if (messageExists(tok)) {
          if (isDeleted(tok)){
            return ("-ERR message %s is deleted", tok);
          } else {
            makeDeleted(tok);
            return ("+OK message %s deleted", tok);
          }
        } else {
          return ("-ERR no such message");
        }

         } else {
        // Invalid command for this state
        return "-ERR invalid command for TRANSACTION";
      } 
      break; // End of TRANSACTION state commands
    } // End of switch
}
