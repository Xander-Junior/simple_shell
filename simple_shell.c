#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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


	signal(SIGINT, sigint_handler);

	while (1)
	{
		printf("$ ");
		getline(&input, &len, stdin);
		if (feof(stdin))
		{
			free(input);
			printf("\n");
			exit(0);
		}
		input_length = strlen(input);
		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}

		if (access(input, F_OK) == -1)
		{
			printf("./shell: No such file or directory\n");
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
			argv[0] = input;
			argv[1] = NULL;
			if (execve(input, argv, NULL) == -1)
			{
				perror("./shell");
			}
			exit(0);
		}
		else
		{
			wait(&status);
		}
	}
	free(input);
	return (0);
}
