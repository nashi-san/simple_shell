#include "shell.h"

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
		path_token = _strtok(path_copy, ":");
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
				path_token = _strtok(NULL, ":");
			}
		}
		free(path_copy);
	}
	return (NULL);
}
