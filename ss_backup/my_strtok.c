#include "shell.h"

char *_strtok(char *str, const char *delimiters)
{
	char *token;
	static char *current;

	if (str != NULL)
	{
		current = str;
	}
	else
	{

		if (current == NULL || *current == '\0')
		{
			return (NULL);
		}
	}
	token = current;

	while (*current != '\0')
	{
		if (strchr(delimiters, *current) != NULL)
		{
			*current = '\0';
			current++;
			return (token);
		}
		current++;
	}

	return (token);
}
