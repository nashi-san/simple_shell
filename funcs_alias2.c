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
	ali_t *end_alias = NULL;
	char *end_value = NULL;
	char *the_end_value;

	while (current != NULL)
	{
		if (_strcmp(current->name, alias_name) == 0)
		{
			end_alias = current;
			alias_name = current->value;
		}
		current = current->next;
	}

	if (end_alias != NULL)
	{
		end_value = find_alias(alias_name, ali_list);
		the_end_value = _strdup(end_value);
		free(end_value);
		return (the_end_value);
	}

	return _strdup(alias_name);
}
