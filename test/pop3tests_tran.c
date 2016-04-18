// Class with tests  for TRANSACTION state

#include <CUnit/CUnit.h> 
#include <CUnit/Basic.h> 
                                    
#include "protocol.h" 

#include <stdio.h>  // for printf 
#include <stdlib.h> 

int init_suite(void) { return 0; } 
int clean_suite(void) { return 0; } 



void tran_correct_commands_test(void){  
// TODO ?? HOW to check if the input is what I want?
// USER, PASS, QUIT (then UPDATE - sign off: delete files created etc)         
// USER, PASS, STAT (check number of messages, size of mailbox)                
// USER, PASS, LIST (check multiple line response - no messages in mailbox)    
// USER, PASS, LIST (check multiple line response - many messages in mailbox)  
// USER, PASS, LIST 1 (check data for the specific message, number of message, size in bytes)  
// USER, PASS, RETR 1 (check size in bytes, message data) 
// USER, PASS, DELE 1 (message 1 exists & is deleted)     
  int state, i, num_of_commands = 21;
  char *command[num_of_commands] = {
                      "USER myuser", "PASS lala1234", "QUIT", 
                      "USER myuser", "PASS lala1234", "STAT",   /* num of messages, size of mailbox */
                      "USER myuser", "PASS lala1234", "LIST",   /* no messages in mailbox */
                      "USER myuser", "PASS lala1234", "LIST",   /* many messages in mailbox */
                      "USER myuser", "PASS lala1234", "LIST 1", 
                      "USER myuser", "PASS lala1234", "RETR 1", 
                      "USER myuser", "PASS lala1234", "DELE 1"}; 
  int expected_state[num_of_commands] = {
                      AUTHORIZATION, TRANSACTION, UPDATE,
                      AUTHORIZATION, TRANSACTION, TRANSACTION,    
                      AUTHORIZATION, TRANSACTION, TRANSACTION,    
                      AUTHORIZATION, TRANSACTION, TRANSACTION,   
                      AUTHORIZATION, TRANSACTION, TRANSACTION,  
                      AUTHORIZATION, TRANSACTION, TRANSACTION,   
                      AUTHORIZATION, TRANSACTION, TRANSACTION};  
                      
  for (i=0; i<num_of_commands; i++) {
    CU_ASSERT_NSTRING_EQUAL("+OK", respond_to_command(&state, &(command[i]), 3);
    CU_ASSERT_EQUAL(expected_state[i], state);
  }
} 

void tran_wrong_commands_test(void){   
// TODO ?? HOW to check if the input is what I want?
// USER, PASS, LALA (invalid command)
// USER, PASS, RETR (number of message must be given in RETR command)
// USER, PASS, DELE (number of message must be given in DELE command)
// USER, PASS, DELE 2 (no such message - message 2 does not exist)
// USER, PASS, DELE 1, LIST 1 (message is deleted)
// USER, PASS, DELE 1, RETR 1 (message is deleted)
// USER, PASS, DELE 1, DELE 1 (message is already deleted)
  int state, i, num_of_commands = 24;
  char *command[num_of_commands] = {
                      "USER myuser", "PASS lala1234", "LALA",   /* invalid command */
                      "USER myuser", "PASS lala1234", "RETR",   /* invalid command - lack of arguments */
                      "USER myuser", "PASS lala1234", "DELE",   /* invalid command - lack of arguments */
                      "USER myuser", "PASS lala1234", "DELE 2", /* 2 does not exist */
                      "USER myuser", "PASS lala1234", "DELE 1", "LIST 1",   /* deleted */
                      "USER myuser", "PASS lala1234", "DELE 1", "RETR 1",   /* deleted */
                      "USER myuser", "PASS lala1234", "DELE 1", "DELE 1"};  /* already deleted */
  int expected_state[num_of_commands] = {
                      AUTHORIZATION, TRANSACTION, TRANSACTION,
                      AUTHORIZATION, TRANSACTION, TRANSACTION,
                      AUTHORIZATION, TRANSACTION, TRANSACTION, 
                      AUTHORIZATION, TRANSACTION, TRANSACTION, 
                      AUTHORIZATION, TRANSACTION, TRANSACTION, TRANSACTION,    
                      AUTHORIZATION, TRANSACTION, TRANSACTION, TRANSACTION,    
                      AUTHORIZATION, TRANSACTION, TRANSACTION, TRANSACTION};   
                      
  for (i=0; i<num_of_commands; i++) {
    CU_ASSERT_NSTRING_EQUAL("-ERR", respond_to_command(&state, &(command[i]), 3);
    CU_ASSERT_EQUAL(expected_state[i], state);
  }
}

/************* Test Runner Code goes here **************/ 
int main ( void ) 
{ 
  CU_pSuite pSuite = NULL; 
 
  /* initialize the CUnit test registry */ 
  if ( CUE_SUCCESS != CU_initialize_registry() ) 
    return CU_get_error(); 

  /* add a suite to the registry */ 
  pSuite = CU_add_suite( "transaction_test_suite", init_suite, clean_suite ); 
  if ( NULL == pSuite ) { 
    CU_cleanup_registry(); 
    return CU_get_error(); 
  } 

  /* add the tests to the suite */ 
  if ( (NULL == CU_add_test(pSuite, "tran_correct_commands_test", tran_correct_commands_test)) || 
       (NULL == CU_add_test(pSuite, "tran_wrong_commands_test", tran_wrong_commands_test)) 
       ) 
    { 
      CU_cleanup_registry(); 
      return CU_get_error(); 
    } 

  // Run all tests using the basic interface 
  CU_basic_set_mode(CU_BRM_VERBOSE); 
  CU_basic_run_tests(); 
  printf("\n"); 
  CU_basic_show_failures(CU_get_failure_list()); 
  printf("\n\n"); 
    
  /* Clean up registry and return */ 
  CU_cleanup_registry(); 
  return CU_get_error(); 
} 
