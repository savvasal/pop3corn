#include "util.h"

int max (int n1, int n2 ) {
  if ( n2 > n1 )  return n2;
  return n1;
}

int getNumberOfThreads(FILE *config_file) {

  int number_of_threads = 0;
  char temp[20];

  fscanf (config_file, "%s %d", temp, &number_of_threads);


  return number_of_threads;
  
}

int getPortNumber(FILE *config_file) {

  int port_number = 0;
  char temp[20];
  
  fscanf (config_file, "%s %d", temp, &port_number);


  return port_number;
  
}

FILE * getUsersFileName(FILE *config_file) {
  
  char users_file_name[20];
  char temp[20];
  FILE *users_file;
  
  fscanf (config_file, "%s %s", temp, users_file_name);
  users_file = fopen(users_file_name, "r");
  if(!users_file) {
    perror("Please initialize a file with users and passwords");
    exit(1);
  }
  
  return users_file;
}

