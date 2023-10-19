#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 1024

int main()
{
	char *input = NULL;
	size_t len = 0;

	while (1)
	{
		printf("$ ");
		getline(&input, &len, stdin);

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
	}
	return (0);
}
