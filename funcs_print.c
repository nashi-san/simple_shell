#include "shell.h"

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
 * _puts_stdout - writes a string to stdout
 * @s: string
 *
 * Return: number of chars written, -1 on error
 */
int _puts_stdout(char *s)
{
	return (write(1, s, _strlen(s)));
}

