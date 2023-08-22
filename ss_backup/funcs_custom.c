#include "shell.h"

/**
 * _getchar - ..
 *
 * Return: ..
 */
int _getchar(void)
{
	char c;
	ssize_t bytes_read = read(STDIN_FILENO, &c, 1);

	if (bytes_read <= 0)
	{
		return (EOF);
	}
	return (c);
}

/**
 * _getline - ..
 * @lineptr: ..
 * @n: ..
 * @stream: ..
 *
 * Return: ..
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t buf_size = BUF_SIZE, buf_newsize, i = 0;
	char *buffer;
	char *new_buffer;
	int c;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	buffer = malloc(buf_size);
	if (buffer == NULL)
		return (-1);
	while ((c = _getchar()) != '\n' && c != EOF)
	{
		if (i >= buf_size - 1)
		{
			buf_newsize = buf_size + BUF_SIZE;
			new_buffer = _realloc(buffer, buf_size, buf_newsize);
			if (new_buffer == NULL)
			{
				free(buffer);
				return (-1);
			}
			buffer = new_buffer;
			buf_size = buf_newsize;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
	if (i == 0 && c == EOF)
	{
		free(buffer);
		return (-1);
	}
	if (*lineptr != NULL)
	{
		free(*lineptr);
	}
	*lineptr = buffer;
	*n = buf_size;
	return (i);
}

/**
 * _which - locates the path of a command
 * @command: command
 *
 * Return: path to executable file if found
 */
char *_which(char *command)
{
	char *path, *path_copy, *path_token, *file_path;
	int command_length, directory_length;

	if (access(command, X_OK) == 0)
		return (strdup(command));
	path = getenv("PATH");
	if (path)
	{
		path_copy = strdup(path);
		if (path_copy == NULL)
			return (NULL);
		command_length = strlen(command);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = (char *)malloc(command_length + directory_length + 2);
			if (file_path == NULL)
			{
				free(path_copy);
				return (NULL);
			}
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			if (access(file_path, X_OK) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
	}
	return (NULL);
}
