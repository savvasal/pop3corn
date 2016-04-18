// Class with tests for AUTHORISATION state

#include <CUnit/CUnit.h> 
#include <CUnit/Basic.h> 
                                    
#include "protocol.h" 

#include <stdio.h>  // for printf 
//#include <stdlib.h> 

int init_suite(void) { return 0; } 
int clean_suite(void) { return 0; } 


void auth_correct_commands_test(void){
  // QUIT
  // USER, QUIT
  // USER, PASS (pass correct for specific user)
  int state, i, num_of_commands = 5;
  char *command[num_of_commands] = {
                      "QUIT",                        
                      "USER myuser", "QUIT", 
                      "USER myuser", "PASS lala1234"}; 
  int expected_state[num_of_commands] = {
                      AUTHORIZATION,
                      AUTHORIZATION, AUTHORIZATION,  /* or UPDATE, AUTHORIZATION */
                      AUTHORIZATION, TRANSACTION};   /* or UPDATE, AUTHORIZATION */
                      
  for (i=0; i<num_of_commands; i++) {
    CU_ASSERT_NSTRING_EQUAL("+OK", respond_to_command(&state, &(command[i]), 3);
    CU_ASSERT_EQUAL(expected_state[i], state);
  }
}       

void auth_wrong_commands_test(void){    
  // PASS (without USER)
  // USER, PASS (correct USER, invalid PASS - mismatch)
  // LALA (invalid command)
  int state, i, num_of_commands = 4;
  char *command[num_of_commands] = {
                      "PASS",                        
                      "USER myuser", "PASS lala1111", /* username valid, password mismatch */
                      "INVALIDCOMMAND"}; 
  int expected_state[num_of_commands] = {
                      AUTHORIZATION,
                      AUTHORIZATION, AUTHORIZATION,
                      AUTHORIZATION};
                      
  for (i=0; i<num_of_commands; i++) {
    CU_ASSERT_NSTRING_EQUAL("-ERR", respond_to_command(&state, &(command[i]), 3);
    CU_ASSERT_EQUAL(expected_state[i], state);
  }
} 


void auth_wrong_commands_test(void){  
// USER, PASS, QUIT (then UPDATE - sign off: delete files created etc)
// USER, PASS, STAT (check number of messages, size of mailbox)
// USER, PASS, LIST (check multiple line response - no messages in mailbox)
// USER, PASS, LIST (check multiple line response - many messages in mailbox)
// USER, PASS, LIST 1 (check data for the specific message, number of message, size in bytes)
// USER, PASS, RETR 1 (check size in bytes, message data)
// USER, PASS, DELE 1 (message 1 exists & is deleted)
  int state, i, num_of_commands = 4;
  char *command[num_of_commands] = {
                      "PASS",                        
                      "USER myuser", "PASS lala1111", /* username valid, password mismatch */
                      "INVALIDCOMMAND"}; 
  int expected_state[num_of_commands] = {
                      AUTHORIZATION,
                      AUTHORIZATION, AUTHORIZATION,
                      AUTHORIZATION};
                      
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
  pSuite = CU_add_suite( "authentication_test_suite", init_suite, clean_suite ); 
  if ( NULL == pSuite ) { 
    CU_cleanup_registry(); 
    return CU_get_error(); 
  } 

  /* add the tests to the suite */ 
  if ( (NULL == CU_add_test(pSuite, "auth_correct_commands_test", authentication_correct_commands_test)) || 
       (NULL == CU_add_test(pSuite, "auth_wrong_commands_test", authentication_wrong_commands_test)) 
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
