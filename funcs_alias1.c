#include "shell.h"
/**
 * alias_builtin - handles the 'alias' built-in command.
 * @line: the input line containing the command and arguments.
 * @cmds: commands
 * @com: sub-command
 * @argv: an array of strings containing the command and arguments.
 * @n: the number of arguments.
 * @exit_status: a pointer to the exit status variable.
 * @ali_list: a double pointer to the head of the alias list
 *
 * Return: Always returns 0.
 */

int alias_builtin(UNUSED char *line, UNUSED char **cmds, UNUSED char *com,
		char **argv, UNUSED int n, UNUSED int *exit_status, ali_t **ali_list)
{

	char *alias_name, *alias_value, *arg;
	int i;

	if (argv[1] == NULL || argv[1][0] == '\0')
		print_alias(*ali_list);
	else
	{
		for (i = 1; argv[i] != NULL; i++)
		{
			arg = argv[i];

			if (strchr(arg, '=') != NULL)
			{
				alias_name = strtok(arg, "=");
				alias_value = strtok(NULL, "=");
				while (alias_name != NULL && alias_value != NULL)
				{
					update_alias(alias_name, alias_value, ali_list);
					alias_name = strtok(NULL, "=");
					alias_value = strtok(NULL, "=");
				}
			}
			else
				print_single_alias(arg, *ali_list);
		}
	}
	return (0);
}

/**
 * print_alias - print all aliases in the linked list
 * @ali_list: a double pointer to the head of the alias list
 */
void print_alias(ali_t *ali_list)
{
	ali_t *current = ali_list;

	while (current != NULL)
	{
		write(STDOUT_FILENO, current->name, _strlen(current->name));
		write(STDOUT_FILENO, "='", 2);
		write(STDOUT_FILENO, current->value, _strlen(current->value));
		write(STDOUT_FILENO, "'\n", 2);
		current = current->next;
	}
}
/**
 * print_single_alias - print one aliase in the linked list
 * @alias_name: the name of the alias to be printed.
 * @ali_list: a double pointer to the head of the alias list
 */
void print_single_alias(char *alias_name, ali_t *ali_list)
{
	ali_t *current = ali_list;

	while (current != NULL)
	{
		if (strcmp(current->name, alias_name) == 0)
		{
			write(STDOUT_FILENO, current->name, strlen(current->name));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, current->value, strlen(current->value));
			write(STDOUT_FILENO, "'\n", 2);
			return;
		}
		current = current->next;
	}
}
/**
 * update_alias - add a new alias or edit an existing one to the linked list
 * @alias_name: the alias name
 * @alias_value: the alias value
 * @ali_list: a double pointer to the head of the alias list
 */
void update_alias(char *alias_name, char *alias_value, ali_t **ali_list)
{
	ali_t *current = *ali_list;

	if (*ali_list == NULL)
	{
		create_alias(alias_name, alias_value, ali_list);
		return;
	}
	while (current != NULL)
	{
		if (_strcmp(current->name, alias_name) == 0)
		{
			free(current->value);
			current->value = strdup(alias_value);
			if (current->value == NULL)
			{
				free(current->value);
				return;
			}
			return;
		}
		current = current->next;
	}
	create_alias(alias_name, alias_value, ali_list);
}
/**
 * create_alias - creates a new alias and adds it to the alias list
 * @alias_name: the name of the alias to be created
 * @alias_value: the value associated with the alias
 * @ali_list: a double pointer to the head of the alias list
 */
void create_alias(char *alias_name, char *alias_value, ali_t **ali_list)
{
	ali_t *new_alias, *current;

	new_alias = malloc(sizeof(ali_t));
	if (new_alias == NULL)
		return;
	new_alias->name = strdup(alias_name);
	new_alias->value = strdup(alias_value);
	if (new_alias->name == NULL || new_alias->value == NULL)
	{
		free(new_alias->name);
		free(new_alias->value);
		free(new_alias);
		return;
	}
	if (*ali_list == NULL)
	{
		new_alias->next = NULL;
		*ali_list = new_alias;
	}
	else
	{
		current = *ali_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_alias;
		new_alias->next = NULL;
	}
}
