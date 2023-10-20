#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/* Function Prototypes */
void sigint_handler(int sig);
int all_spaces(char *str);

#endif /* MAIN_H */
