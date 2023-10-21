#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


#define INPUT_SIZE 1024



#include "main.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 * Description: This function handles the Ctrl+C signal to ensure that
 * the shell prompt is displayed again after the signal is received.
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "$ ", 10);
	fflush(stdout);
}

/**
 * all_spaces - checks if a string is composed only of spaces or tabs.
 * @str: The string to check.
 *
 * Return: 1 if the string is all spaces or tabs, 0 otherwise.
 */
int all_spaces(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

/**
 * trim - Removes leading and trailing white spaces from a string.
 * @str: The string to trim.
 *
 * Return: Pointer to the trimmed string.
 */
char* trim(char *str)
{
	char *end;

	while(isspace((unsigned char)*str)) str++;
	if(*str == 0)
		return (str);
	end = str + strlen(str) - 1;
	while(end > str && isspace((unsigned char)*end)) end--;
	*(end+1) = 0;

	return (str);
}

/**
 * main - Entry point for the shell program.
 * @void: No parameters.
 *
 * Description: Starts a loop that continuously displays a prompt,
 * waits for user input, and executes the provided command.
 * Commands without arguments are supported.
 *
 * Return: Always returns 0 (successful exit).
 */
int main(void)
{
	char *input = NULL;
	size_t len = 0;
	pid_t child_pid;
	int status;
	ssize_t input_length;
	char *argv[2];
	char *command;


	signal(SIGINT, sigint_handler);

	while (1)
	{
		printf("$ ");
		getline(&input, &len, stdin);

		command = strtok(input, "\n");
		while (command != NULL)
		{
			command = trim(command);
			if (strlen(command) == 0)
			{
				command = strtok(NULL, "\n");
				continue;
			}

			if (feof(stdin))
			{
				printf("\n");
				break;
			}

			input_length = strlen(command);
			if (input_length > 0 && command[input_length - 1] == '\n')
			{
				command[input_length - 1] = '\0';
			}

			if (access(command, F_OK) == -1)
			{
				printf("./shell: No such file or directory\n");
				command = strtok(NULL, "\n");
				continue;
			}

			child_pid = fork();
			if (child_pid == -1)
			{
				perror("Error");
				free(input);
				exit(1);
			}

			if (child_pid == 0)
			{
				argv[0] = command;
				argv[1] = NULL;
				if (execve(command, argv, NULL) == -1)
				{
					perror("./shell");
				}
				exit(0);
			}
			else
			{
				wait(&status);
			}

			command = strtok(NULL, "\n");
		}
	}
	free(input);
	return (0);
}

