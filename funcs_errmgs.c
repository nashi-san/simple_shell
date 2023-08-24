#include "shell.h"

/**
 * err_msg_cmd - writes an error msg to stderr
 * @argv: array of tokens
 * @n: count of commands
 *
 * Return: void
 */
void err_msg_cmd(char **argv, int n)
{
	char *n_str;

	n_str = n_conversion(n);

	_puts_stderr("./hsh: ");
	_puts_stderr(n_str);
	_puts_stderr(": ");
	_puts_stderr(argv[0]);
	_puts_stderr(": not found\n");

	free(n_str);
}

/**
 * err_msg_exit - writes an error msg to stderr
 * @status: input status of exit
 * @n: count of commands
 *
 * Return: void
 */
void err_msg_exit(char *status, int n)
{
	char *n_str;

	n_str = n_conversion(n);

	_puts_stderr("./hsh: ");
	_puts_stderr(n_str);
	_puts_stderr(": exit: Illegal number: ");
	_puts_stderr(status);
	_puts_stderr("\n");

	free(n_str);
}

/**
 * err_msg_cd - writes an error msg to stderr
 * @argv: array of tokens
 * @n: count of commands
 *
 * Return: void
 */
void err_msg_cd(char **argv, int n)
{
	char *n_str;

	n_str = n_conversion(n);

	_puts_stderr("./hsh: ");
	_puts_stderr(n_str);
	_puts_stderr(": ");
	_puts_stderr(argv[0]);
	_puts_stderr(": can't cd to ");
	_puts_stderr(argv[1]);
	_puts_stderr("\n");

	free(n_str);
}

/**
 * err_msg_file - writes an error msg to stderr
 * @argv: array of tokens
 * @n: count of commands
 *
 * Return: void
 */
void err_msg_file(char **argv, int n)
{
	char *n_str;

	n_str = n_conversion(n);

	_puts_stderr("./hsh: ");
	_puts_stderr(n_str);
	_puts_stderr(": Can't open ");
	_puts_stderr(argv[1]);
	_puts_stderr("\n");

	free(n_str);
}
