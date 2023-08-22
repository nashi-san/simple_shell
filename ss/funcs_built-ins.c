#include "shell.h"

/**
 * env_builtin - prints the current environment
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 *
 * Return: 0 on success
 */
int env_builtin(__attribute__((unused)) char *line,
		__attribute__((unused)) char **argv,
		__attribute__((unused)) int n,
		__attribute__((unused)) int *exit_status)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

/**
 * exit_builtin - exits the shell with a specific status
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 *
 * Return: 0 on success
 */
int exit_builtin(char *line, char **argv, int n, int *exit_status)
{
	int i, is_valid, status_converted;
	char *status = argv[1];

	if (status != NULL)
	{
		is_valid = 1;
		for (i = 0; status[i]; i++)
		{
			if (!isdigit(status[i]))
			{
				is_valid = 0;
				break;
			}
		}
		status_converted = _atoi(status);
		if (is_valid && status_converted > 0)
		{
			free_array(argv);
			free(line);
			exit(status_converted);
		}
		else
		{
			/* fprintf(stderr, "./hsh: %d: exit: Illegal number: %s\n", n, status);*/
			err_msg_exit(status, n);
			*exit_status = 2;
			return (0);
		}
	}
	else
	{
		free_array(argv);
		free(line);
		exit(*exit_status);
	}
	return (0);
}
