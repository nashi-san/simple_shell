#include "shell.h"
/**
 * find_alias - return the value of an alias.
 * @alias_name: the alias name
 * @ali_list: a double pointer to the head of the alias list
 *
 * Return: alias value on success, null on failure.
 */
char *find_alias(char *alias_name, ali_t **ali_list)
{
	ali_t *current = *ali_list;

	while (current != NULL)
	{
		if (_strcmp(current->name, alias_name) == 0)
		{

			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}
