#include "shell.h"
/**
 * execute_commands - executes multiple commands separated by semicolons.
 * @line: the input line containing multiple commands.
 * @ali_list: a double pointer to the alias list head.
 * @n: The current line number.
 * @exit_status: a pointer to the exit status variable.
 * Return: The final exit status after executing all commands.
 *
 */
int execute_commands(char *line, ali_t **ali_list, int n, int *exit_status)
{
	char *command = strdup(line);
	char *token = strtok(command, ";");
	char **argv;
	int argc, is_builtin;

	while (token != NULL)
	{
		argv = process_line(token, &argc);
		if (argc != 0)
		{
			is_builtin = execute_builtin(token, argv, n, exit_status, ali_list);
			if (is_builtin == 1)
				*exit_status = exe(argv, n, ali_list);
		}
		free_array(argv);
		token = strtok(NULL, ";");
	}
	free(command);

	return (*exit_status);
}
/**
 * main - interprets a UNIX command line
 *
 * Return: 0 on success
 */
int main(void)
{
	ali_t *ali_list = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = 0, n = 0, exit_status = 0;

	copy_environ();
	if (isatty(STDIN_FILENO))
		interactive = 1;
	while (1)
	{
		if (interactive == 1)
			_puts_stdout("$ ");
		n++;
		nread = _getline(&line, &len, stdin);
		handle_comment(line);
		if (nread != -1)
		{
			exit_status = execute_commands(line, &ali_list, n, &exit_status);
		}
		else
		{
			if (interactive == 1)
				_putchar('\n');
			cleanup(&ali_list, env_copy, line);
			return (exit_status);
		}
	}
	cleanup(&ali_list, env_copy, line);
	return (0);
}
