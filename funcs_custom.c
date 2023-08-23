#include "shell.h"

/**
 * _getchar - reads a character from standard input
 *
 * Return: the character read, or EOF on failure or end of file
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
 * _getline - reads a line from a file stream
 * @lineptr: a double pointer pointer to the buff to store the read line
 * @n: pointer to the size of the buffer
 * @stream: file stream to read from
 *
 * Return: the number of characters read, or -1 on failure
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
 * _strtok - tokenizes a string
 * @str: string
 * @delimiters: delimiters
 *
 * Return: token, NULL if no token was found
 */
char *_strtok(char *str, char *delimiters)
{
	char *token;
	static char *current;

	if (str != NULL)
	{
		current = str;
	}
	else
	{
		if (current == NULL || *current == '\0')
			return (NULL);
	}

	while (*current != '\0' && strchr(delimiters, *current) != NULL)
	{
		current++;
	}
	if (*current == '\0')
		return (NULL);

	token = current;
	while (*current != '\0' && strchr(delimiters, *current) == NULL)
	{
		current++;
	}
	if (*current == '\0')
		return (token);

	*current = '\0';
	current++;

	return (token);
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
		return (_strdup(command));
	path = _getenv("PATH");
	if (path)
	{
		path_copy = _strdup(path);
		if (path_copy == NULL)
			return (NULL);
		command_length = _strlen(command);
		path_token = _strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = _strlen(path_token);
			file_path = malloc(command_length + directory_length + 2);
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
				path_token = _strtok(NULL, ":");
			}
		}
		free(path_copy);
	}
	return (NULL);
}
