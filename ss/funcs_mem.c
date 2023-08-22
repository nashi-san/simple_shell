#include "shell.h"

/**
 * free_array - frees an array
 * @argv: array of tokens
 *
 * Return: void
 */
void free_array(char **argv)
{
	int i = 0;

	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
/**
 * _memcpy - copy m bytes from m1 to m2
 * @dest: 1st memory block
 * @src: 2nd memory block
 * @m: number of bytes to copy
 *
 * Return: pointer to memory block
 */
char *_memcpy(char *dest, char *src, unsigned int m)
{
	unsigned int i;

	i = 0;
	while (i < m)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}


/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to previous memory block
 * @old_size: size in bytes of previous memory block
 * @new_size: size in bytes of new memory block
 *
 * Return: pointer to the new allocated memory, NULL on failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int min;
	void *new_ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}
	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	if (new_size < old_size)
		min = new_size;
	else
		min = old_size;
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	new_ptr = _memcpy(new_ptr, ptr, min);
	free(ptr);
	return (new_ptr);
}
int unsetenv_builtin(__attribute__((unused)) char *line, char **argv,
		__attribute__((unused)) int n, int *exit_status)
{
	if (argv[1] == NULL)
	{
		*exit_status = 0;
		return (0);
	}

	return (_unsetenv(argv[1], exit_status));
}

int _unsetenv(char *variable, int *exit_status)
{
	int i, j;
	int found = 0;
	int variable_len = _strlen(variable);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], variable, variable_len) == 0
				&& environ[i][variable_len] == '=')
		{
			found = 1;
			break;
		}
	}
	if (found)
	{
		for (j = i; environ[j] != NULL; j++)
		{
			environ[j] = environ[j + 1];
		}
		*exit_status = 1;
		return (1);
	}
	else
	{
		*exit_status = 0;
		return (0);
	}
}
