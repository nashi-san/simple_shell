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
		argv[i] = NULL;
		i++;
	}
	free(argv);
}
/**
 * free_aliases - frees the memory allocated for the alias list
 * @ali_list: a double pointer to the head of the alias list
 */
void free_aliases(ali_t **ali_list)
{
	ali_t *current = *ali_list;
	ali_t *next;

	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*ali_list = NULL;
}
/**
 * cleanup - frees allocated memory for aliases and environment copy.
 * @ali_list: a double pointer to the head of alias list.
 * @env_copy: a double pointer to the environment copy.
 * @line: a pointer to a string representing the line of command
 */
void cleanup(ali_t **ali_list, char **env_copy, char *line)
{
	free_aliases(ali_list);
	free_array(env_copy);
	free(line);
}
/**
 * _memcpy - copy m bytes from m1 to m2
 * @dest: 1st memory block
 * @src: 2nd memory block
 * @m: number of bytes to copy
 *
 * Return: pointer to memory block
 */
char *_memcpy(char *dest, const char *src, unsigned int m)
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
