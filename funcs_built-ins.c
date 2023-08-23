#include "shell.h"

/**
 * env_builtin - prints the current environment vars
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
		__attribute__((unused)) int *exit_status,
		char ***env_copy)
{
	int i = 0;

	while ((*env_copy)[i] != NULL)
	{
		_puts_stdout((*env_copy)[i]);
		_putchar('\n');
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
 * Return: 0 on failure, otherwise exits with an exit status
 */
int exit_builtin(char *line, char **argv, int n, int *exit_status,
		__attribute__((unused)) char ***env_copy)
{
	int i, is_valid, status_converted;
	char *status = argv[1];

	if (status != NULL)
	{
		is_valid = 1;
		for (i = 0; status[i]; i++)
		{
			if (!_isdigit(status[i]))
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

/**
 * cd_builtin - handles the cd builtin
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 *
 * Return: 0 on success
 */
int cd_builtin(__attribute__((unused)) char *line,
		char **argv, int n,
		__attribute__((unused)) int *exit_status,
		__attribute__((unused)) char ***env_copy)
{
	char curr_dir[BUF_SIZE];
	char *home_dir = _getenv("HOME"), *prev_dir = _getenv("OLDPWD");

	if (argv[1] != NULL)
	{
		if (_strcmp(argv[1], "-") == 0)
		{
			if (prev_dir != NULL)
			{
				_puts_stdout(prev_dir), _putchar('\n');
				if (chdir(prev_dir) != 0)
					return (-1);
			}
			else
			{
				if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
				{
					_puts_stdout(curr_dir), _putchar('\n');
				}
				else
					return (-1);
			}
		}
		else
		{
			if (chdir(argv[1]) != 0)
			{
				err_msg_cd(argv, n);
				return (-1);
			}
		}
	}
	else
	{
		if (home_dir != NULL && chdir(home_dir) != 0)
			return (-1);
	}
	cd_update_env();
	return (0);
}

/**
 * cd_update_env - updates the oldpwd and pwd in env
 *
 * Return: void
 */
void cd_update_env(void)
{
	char curr_dir[BUF_SIZE];

	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
	{
		setenv("OLDPWD", _getenv("PWD"), 1);
		setenv("PWD", curr_dir, 1);
	}
	else
	{
		perror("getcwd");
	}
}
