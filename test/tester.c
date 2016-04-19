// Class with tests  for TRANSACTION state

#include <CUnit/CUnit.h> 
#include <CUnit/Basic.h> 

#include "../src/server.h"

#include <stdio.h>  // for printf 
#include <stdlib.h> 

int init_suite(void) { return 0; } 
int clean_suite(void) { return 0; }

void test_case_sample(void)
{
   CU_ASSERT(CU_TRUE);
   CU_ASSERT_NOT_EQUAL(2, -1);
   CU_ASSERT_STRING_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #2");

   CU_ASSERT(CU_FALSE);
   CU_ASSERT_EQUAL(2, 3);
   CU_ASSERT_STRING_NOT_EQUAL("string #1", "string #1");
   CU_ASSERT_STRING_EQUAL("string #1", "string #2");
}

void server_socket_test(void){
  int port = 30000;
  int socket_fd = new_server_socket(port);
  CU_TEST(socket_fd);
  CU_ASSERT_EQUAL(close_server_socket(socket_fd),0);
  
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
  if ( (NULL == CU_add_test(pSuite, "server_socket_test", server_socket_test))
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
