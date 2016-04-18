#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define AUTHORIZATION 0
#define TRANSACTION 1
#define UPDATE 2

#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define MAX_STRING 128

FILE *users_file; 
char username[MAX_USERNAME];
char password[MAX_PASSWORD];

void respondToCommand(int *state, char *command, char *return_value);
int initializeProtocol(char *users_filename);
int isValidUsername(char *username);
int isCorrectPassword(char *password);

#endif
