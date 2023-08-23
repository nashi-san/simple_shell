#include "shell.h"

/**
 * _unsetenv - unsets an environment variable
 * @variable: The name of the variable
 *
 * Return: 0 on success, 1 on failure
 */
int _unsetenv(char *variable)
{
	int i, j;
	int found = 0;
	int variable_len = _strlen(variable);

	for (i = 0; env_copy[i] != NULL; i++)
	{
		if (_strncmp(env_copy[i], variable, variable_len) == 0
				&& env_copy[i][variable_len] == '=')
		{
			found = 1;
			break;
		}
	}
	if (found != 1)
	{
		_puts_stderr("variable not found\n");
		return (-1);
	}
	else
	{
		free(env_copy[i]);
		for (j = i; env_copy[j] != NULL; j++)
		{
			env_copy[j] = env_copy[j + 1];
		}
	}
	return (0);
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
	if (argv[1] == NULL)
	{
		return (0);
	}
	return (_unsetenv(argv[1]));
}

/**
 * _setenv - sets the value of an environment variable
 * @variable: The name of the variable
 * @value: The value to set for the variable
 *
 * Return: 0 on success, 1 on failure
 */
int _setenv(char *variable, char *value)
{
	int i;
	char *new_entry = malloc(strlen(variable) + strlen(value) + 2);

	if (new_entry == NULL)
	{
		return (-1);
	}

	strcpy(new_entry, variable);
	strcat(new_entry, "=");
	strcat(new_entry, value);

	for (i = 0; env_copy[i] != NULL; i++)
	{
		if (strncmp(env_copy[i], variable, strlen(variable)) == 0 &&
				env_copy[i][strlen(variable)] == '=')
		{
			free(env_copy[i]);
			env_copy[i] = strdup(new_entry);
			free(new_entry);
			return (0);
		}
	}

	env_copy = realloc(env_copy, (i + 2) * sizeof(char *));
	if (env_copy == NULL)
	{
		free(new_entry);
		return (-1);
	}

	env_copy[i] = strdup(new_entry);
	env_copy[i + 1] = NULL;
	free(new_entry);
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
		return (0);
	}
	return (_setenv(argv[1], argv[2]));
}

/**
 * copy_environ - copies all environ vars in copy_env
 *
 * Return: void
 */
void copy_environ(void)
{
	int var_count = 0;
	int i;

	while (environ[var_count] != NULL)
	{
		var_count++;
	}

	env_copy = malloc((var_count + 1) * sizeof(char *));
	if (env_copy == NULL)
	{
		perror("memory allocation");
		return;
	}

	for (i = 0; i < var_count; i++)
	{
		env_copy[i] = _strdup(environ[i]);
		if (env_copy[i] == NULL)
		{
			perror("memory allocation");
			free_array(env_copy);
			return;
		}
	}
	env_copy[var_count] = NULL;
}
