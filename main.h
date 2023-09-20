#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void prompt(void);
char *read_line(void);
void execute_command(char *command);

#endif /* MAIN_H */
