#include "main.h"
#include <sys/wait.h>

/**
 * main - Entry point for the shell.
 * Return: Always 0.
 */
int main(void)
{
	char *command;

	while (1)
	{
		prompt();
		command = read_line();
		if (!command)
		{
			break;
		}
		execute_command(command);
		free(command);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * prompt - Display a prompt for the user.
 */
void prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * read_line - Read a line from stdin.
 * Return: The line read from stdin.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;

	if (getline(&line, &len, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}


/**
 * Tokenize the input command line into individual words
 */
char **tokenize_input(char *command)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("#cisfun");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("#cisfun");
				exit(EXIT_FAILURE);
			}
		}


		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute_command - Execute a given command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];
	char *bin_command = NULL;

	size_t len = strlen(command);
	if (len > 0 && command[len - 1] == '\n')
	{
		command[len - 1] = '\0';
	}

	argv[0] = command;
	argv[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (command[0] != '/')
		{
			bin_command = malloc(strlen(command) + 6);
			if (!bin_command)
			{
				perror("#cisfun");
				exit(EXIT_FAILURE);
			}
			strcpy(bin_command, "/bin/");
			strcat(bin_command, command);
			argv[0] = bin_command;
		}

		if (execve(command, argv, NULL) == -1)
		{
			perror(argv[0]);
			free(bin_command);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("#cisfun");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(bin_command);
}
