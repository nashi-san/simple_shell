#include "shell.h"

/**
 * _getenv - gets the value of an environ variable
 * @variable: variable name
 *
 * Return: string
 */
char *_getenv(char *variable)
{
	char *value = NULL;
	int i = 0;
	int variable_len = _strlen(variable);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], variable, variable_len) == 0)
		{
			value = _strchr(environ[i], '=');
			if (value != NULL)
			{
				value++;
				return (value);
			}
		}
	}
	return (NULL);
}
/**
 * unsetenv_builtin - Built-in function to unset environment variable
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: Pointer to the exit status
 *
 * Return: 0 on success, 1 on failure
 */
int unsetenv_builtin(__attribute__((unused)) char *line, char **argv,
		__attribute__((unused)) int n, __attribute__((unused)) int *exit_status)
{
	char *variable = argv[1];
	int i, j;
	int found = 0;
	int variable_len = _strlen(variable);

	if (argv[1] != NULL && argv[2] == NULL)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			if (_strncmp(environ[i], variable, variable_len) == 0
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
			return (0);
		}
	}
	return (1);
}

/**
 * _setenv - Sets the value of an environment variable
 * @variable: The name of the variable
 * @value: The value to set for the variable
 * @exit_status: Pointer to the exit status variable
 *
 * Return: 0 on success, 1 on failure
 */
int _setenv(char *variable, char *value)
{
	int i;
	char *new_var = malloc(strlen(variable) + strlen(value) + 2);

	if (new_var == NULL)
	{
		return (-1);
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
			return (0);
		}
	}
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * setenv_builtin - Built-in function to set environment variable
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 *
 * Return: 0 on success, 1 on failure
 */
int setenv_builtin(__attribute__((unused)) char *line, char **argv,
		__attribute__((unused)) int n, __attribute__((unused)) int *exit_status)
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		return (1);
	}
	return (_setenv(argv[1], argv[2]));
}
