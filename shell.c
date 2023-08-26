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
	char *line = NULL, **cmds;
	size_t len = 0;
	ssize_t nread = 0;
	int interactive = 0, n = 0, exit_status = 0, is_builtin = 1, i, cmds_c = 0;

	copy_environ();
	(isatty(STDIN_FILENO)) ? interactive = 1 : 0;
	while (1)
	{
		(interactive == 1) ? _puts_stdout("$ ") : 0;
		n++;
		nread = _getline(&line, &len, stdin);
		handle_comment(line);
		if (nread != -1)
		{
			cmds = process_line(line, &cmds_c, ";");
			for (i = 0; i < cmds_c; i++)
			{
				argv = process_line(cmds[i], &argc, " \t\n");
				if (argc != 0)
				{
					is_builtin = execute_builtin(line, cmds, cmds[i], argv, n,
							&exit_status, &ali_list);
					if (is_builtin == 1)
						exit_status = exe(argv, n, &ali_list);
				}
				free_array(argv);
			}
			free_array(cmds);
		}
		else
		{
			(interactive == 1) ? _putchar('\n') : 0;
			cleanup(&ali_list, env_copy, line);
			return (exit_status);
		}
	}
	cleanup(&ali_list, env_copy, line);
	return (0);
}
