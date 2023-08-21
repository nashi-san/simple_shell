#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t buf_size = BUF_SIZE, i = 0;
	ssize_t result;
	char *buffer, *new_buffer, c;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	fflush(stdout);
	buffer = malloc(buf_size);
	if (buffer == NULL)
		return (-1);
	while (1)
	{
		result = read_line(&c);
		if (result < 0)
		{
			free(buffer);
			return (-1);
		}
		else if (result == 0)
			break;
		if (c == '\n')
			break;
		if (i >= buf_size - 1)
		{
			buf_size += BUF_SIZE;
			new_buffer = realloc(buffer, buf_size);
			if (new_buffer == NULL)
			{
				free(buffer);
				return (-1);
			}
			buffer = new_buffer;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	if (*lineptr == NULL)
	{
		if (i > BUF_SIZE)
			*n = i;
		else
			*n = BUF_SIZE;
		*lineptr = buffer;
	}
	else if (*n < i)
	{
		if (i > BUF_SIZE)
			*n = i;
		else
			*n = BUF_SIZE;
		*lineptr = buffer;
	}
	else
	{
		strcpy(*lineptr, buffer);
		free(buffer);
	}
	return (i);
}
ssize_t read_line(char *buffer)
{
	char c;
	ssize_t result = read(STDIN_FILENO, &c, 1);

	if (result < 0)
	{
		return (-1);
	}
	else if (result == 0)
	{
		return (0);
	}
	*buffer = c;
	return (1);
}
