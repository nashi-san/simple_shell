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
 * _putchar - writes the character c to stdout
 * @c: character to print
 *
 * Return: 1 on success, -1 on error
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts_stderr - writes a string to stderr
 * @s: string
 *
 * Return: number of chars written, -1 on error
 */
int _puts_stderr(char *s)
{
	return (write(2, s, _strlen(s)));
}

/**
 * _puts_stdout - prints a string to stdout
 * @str: string
 *
 * Return: void
 */
void _puts_stdout(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}
