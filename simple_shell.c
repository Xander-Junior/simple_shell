#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_SIZE 1024

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
	char *argv[2] = {NULL, NULL};
	char *envp[] = {NULL};
	ssize_t read;
	ssize_t input_length;

	while (1)
	{
		printf("$ ");
		read = getline(&input, &len, stdin);
		input_length = strlen(input);

		if (read == -1)
		{
			printf("\n");
			free(input);
			exit(0);
		}
		if (input_length > 0 && input[input_length - 1] == '\n')
		{
			input[input_length - 1] = '\0';
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0);
		}

		argv[0] = input;
		if (execve(argv[0], argv, envp) == -1)
		{
			printf("./shell: No such file or directory\n");
		}
	}
	return (0);
}
