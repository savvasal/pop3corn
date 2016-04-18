#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <stdlib.h>

extern int getNumberOfThreads(FILE *config_file);
extern int getPortNumber(FILE *config_file);
extern FILE * getUsersFileName(FILE *config_file);

#endif
