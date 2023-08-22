#include "shell.h"

/**
 * setenv_builtin - Built-in function to set environment variable
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 *
 * Return: 1 on success, 0 on failure
 */
int setenv_builtin(__attribute__((unused)) char *line, char **argv,
		__attribute__((unused)) int n, int *exit_status)
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		*exit_status = 0;
		return (0);
	}
	return (_setenv(argv[1], argv[2], exit_status));
}
/**
 * _setenv - Sets the value of an environment variable
 * @variable: The name of the variable
 * @value: The value to set for the variable
 * @exit_status: Pointer to the exit status variable
 *
 * Return: 1 on success, 0 on failure
 */
int _setenv(char *variable, char *value, int *exit_status)
{
	int i;
	char *new_var = malloc(strlen(variable) + strlen(value) + 2);

	if (new_var == NULL)
	{
		*exit_status = 0;
		return (0);
	}

	strcpy(new_var, variable);
	strcat(new_var, "=");
	strcat(new_var, value);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], variable, strlen(variable)) == 0
			&& environ[i][strlen(variable)] == '=')
		{
			environ[i] = new_var;
			*exit_status = 1;
			return (1);
		}
	}
	environ[i] = new_var;
	environ[i + 1] = NULL;
	*exit_status = 1;
	return (1);
}

int unsetenv_builtin(__attribute__((unused)) char *line, char **argv,
		__attribute__((unused)) int n, int *exit_status)
{
	if (argv[1] == NULL)
	{
		*exit_status = 0;
		return (0);
	}

	return (_unsetenv(argv[1], exit_status));
}

int _unsetenv(char *variable, int *exit_status)
{
	int i, j;
	int found = 0;
	int variable_len = _strlen(variable);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], variable, variable_len) == 0
				&& environ[i][variable_len] == '=')
		{
			found = 1;
			break;
		}
	}
	if (found)
	{
		for (j = i; environ[j] != NULL; j++)
		{
			environ[j] = environ[j + 1];
		}
		*exit_status = 1;
		return (1);
	}
	else
	{
		*exit_status = 0;
		return (0);
	}
}
