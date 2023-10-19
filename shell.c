#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INPUT_SIZE 1024

int main()
{
	char *input = NULL;
	size_t len = 0;
	char *argv[2] = {NULL, NULL};
	char *envp[] = {NULL};

	while (1)
	{
		printf("$ ");
		ssize_t read = getline(&input, &len, stdin);
		if (read == -1)
		{
			printf("\n");
			free(input);
			exit(0);
		}

		size_t input_length = strlen(input);
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
