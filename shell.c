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
		execute_command(command);
		free(command);
	}
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

	getline(&line, &len, stdin);
	return (line);
}

/**
 * execute_command - Execute a given command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid, wpid;
	int status;
	char *argv[] = {command, NULL};

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror("#cisfun");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("#cisfun");
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		}
		while
		{
			(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
}
