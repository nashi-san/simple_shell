#include "shell.h"

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t buf_size = BUF_SIZE, i = 0;
	char *buffer;
	char *new_buffer;

	int c;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	buffer = malloc(buf_size);
	if (buffer == NULL)
		return (-1);
	while ((c = getchar()) != '\n')
	{
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
	if (*lineptr != NULL)
	{
		free(*lineptr);
	}
	*lineptr = buffer;
	*n = buf_size;
	return (i);
}
