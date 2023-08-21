#include "shell.h"

/**
 * exe - load the path to a command to be executed
 * @argv: array of tokens
 * @n: count of commands
 *
 * Return: exit status
 */
int exe(char **argv, int n)
{
	char *path = NULL;
	int exit_status;

	path = _which(argv[0]);
	if (path == NULL)
	{
		/* fprintf(stderr, "./hsh: %d: %s: not found\n", n, argv[0]);*/
		err_msg_cmd(argv, n);
		exit_status = 127;
	}
	else
	{
		exit_status = execute_command(argv, path);
		free(path);
	}
	return (exit_status);
}

/**
 * handle_comment - removes any comment within a command
 * @line: command line (input)
 *
 * Return: void
 */
void handle_comment(char *line)
{
	int i;

	if (line[0] == '#')
	{
		line[0] = '\0';
		return;
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '#' && line[i - 1] == ' ')
		{
			line[i] = '\0';
			return;
		}
		i++;
	}
}
/**
 * process_line - tokenizes a string
 * @line: command line (input)
 * @argc: count of tokens
 *
 * Return: array of tokens
 */
char **process_line(char *line, int *argc)
{
	char **array = NULL, **new_array = NULL, *token, *delim = " \t\n";
	size_t i = 0, size, new_size;

	size = BUF_SIZE;
	array = (char **)malloc(size * sizeof(char *));
	if (!array)
	{
		perror("Memory allocation error"), exit(1);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		if (i >= size)
		{
			new_size = size * 2;
			new_array = (char **)_realloc(array, size, new_size * sizeof(char *));
			if (!new_array)
			{
				perror("Memory allocation error"), exit(1);
			}
			array = new_array;
			size = new_size;
		}
		array[i] = strdup(token);
		if (!array[i])
		{
			perror("Memory allocation error"), exit(1);
		}
		i++;
		token = strtok(NULL, delim);
	}
	new_array = (char **)_realloc(array, size, (i + 1) * sizeof(char *));
	if (!new_array)
	{
		perror("Memory allocation error"), exit(1);
	}
	array = new_array;
	array[i] = NULL;
	*argc = i;
	return (array);
}
/**
 * execute_builtin - handles built-ins
 * @line: command line (input)
 * @argv: array of tokens
 * @n: count of commands
 * @exit_status: exit status
 *
 * Return: 0 on success, -1 otherwise
 */
int execute_builtin(char *line, char **argv, int n, int *exit_status)
{
	builtin_t builtins[] = {
		{"exit", exit_builtin},
		{"env", env_builtin},
		{NULL, NULL}
	};

	int i;

	for (i = 0; builtins[i].name != NULL; i++)
	{
		if (_strcmp(argv[0], builtins[i].name) == 0)
		{
			return (builtins[i].function(line, argv, n, exit_status));
		}
	}
	return (-1);
}

/**
 * execute_command - calls execve to execute a command
 * @argv: array of tokens
 * @path: file path
 *
 * Return: exit status of execve on success, -1 on failure
 */
int execute_command(char **argv, char *path)
{
	pid_t child_pid;
	int status, exit_status = 0;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("execve");
			return (-1);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}
