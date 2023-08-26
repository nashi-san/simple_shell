#include "shell.h"

/**
 * env_builtin - prints the current environment vars
 * @line: command line (input)
 * @cmds: commands
 * @com: sub-command
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 * @ali_list: a double pointer to the aliases list
 *
 * Return: 0 on success
 */
int env_builtin(UNUSED char *line, UNUSED char **cmds, UNUSED char *com,
		UNUSED char **argv, UNUSED int n, UNUSED int *exit_status,
		UNUSED ali_t **ali_list)
{
	int i = 0;

	while (env_copy[i] != NULL)
	{
		_puts_stdout(env_copy[i]);
		_putchar('\n');
		i++;
	}
	return (0);
}

/**
 * exit_builtin - exits the shell with a specific status
 * @line: command line (input)
 * @cmds: commands
 * @com: sub-command
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 * @ali_list: a double pointer to the aliases list
 *
 * Return: 0 on failure, otherwise exits with an exit status
 */
int exit_builtin(char *line, char **cmds, char *com, char **argv, int n,
		int *exit_status, ali_t **ali_list)
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
			cleanup(ali_list, env_copy, line);
			free_array(argv);
			free(com);
			free(cmds);
			exit(status_converted);
		}
		else
		{
			err_msg_exit(status, n);
			*exit_status = 2;
			return (0);
		}
	}
	else
	{
		cleanup(ali_list, env_copy, line);
		free_array(argv);
		free(com);
		free(cmds);
		exit(*exit_status);
	}
	return (0);
}
/**
 * cd_builtin - handles the cd builtin
 * @line: command line (input)
 * @cmds: commands
 * @com: sub-command
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 * @ali_list: a double pointer to the aliases list
 *
 * Return: 0 on success
 */
int cd_builtin(UNUSED char *line, UNUSED char **cmds, UNUSED char *com,
		char **argv, int n, UNUSED int *exit_status, UNUSED ali_t **ali_list)
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
		_setenv("OLDPWD", _getenv("PWD"));
		_setenv("PWD", curr_dir);
	}
	else
	{
		perror("getcwd");
	}
}
