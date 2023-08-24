#include "shell.h"
/**
 * main - interprets a UNIX command line
 * @argc: count of tokens
 * @argv: array of tokens
 *
 * Return: 0 on success
 */

int main(int argc, char **argv)
{
	ali_t *ali_list = NULL;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = 0, n = 0, exit_status = 0, is_builtin = 1;

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
			argv = process_line(line, &argc);
			if (argc != 0)
			{
				is_builtin = execute_builtin(line, argv, n, &exit_status, &ali_list);
				if (is_builtin == 1)
					exit_status = exe(argv, n);
			}
			free_array(argv);
		}
		else
		{
			if (interactive == 1)
				_putchar('\n');
			free(line);
			cleanup(&ali_list, env_copy);
			return (exit_status);
		}
	}
	free(line);
	cleanup(&ali_list, env_copy);
	return (0);
}
