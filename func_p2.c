#include "main.h"
void printenv(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
	printf("%s\n", environ[i]);
i++;
}
}
char *_getenv(const char *name)
{
	int i = 0;
	char *env_name, *env_value, *value_copy;

if (name == NULL || environ == NULL)
{
return (NULL);
}
for (i = 0; environ[i] != NULL; i++)
{
env_name = strtok(environ[i], "=");
if (env_name != NULL && _strcmp(env_name, name) == 0)
{
env_value = strtok(NULL, "=");
if (env_value == NULL)
{
return (NULL);
}
value_copy = strdup(env_value);
if (value_copy == NULL)
{
return (NULL);
}
return (value_copy);
}
}
return (NULL);
}
/**
* add_node_end - adds a new variable value to the list_path.
* @head: the head of the linked list
* @value: the environment variable path
* Return: the address of the new element, or NULL if it failed
*/
list_path *add_node_end(list_path **head, const char *value)
{
list_path *new, *tail;
if (value == NULL)
return (NULL);
new = malloc(sizeof(list_path));
if (new == NULL)
{
return (NULL);
}
new->str = strdup(value);
if (new->str == NULL)
{
free(new);
return (NULL);
}
new->next = NULL;
if (*head == NULL)
*head = new;
else
{
tail = *head;
while (tail->next != NULL)
tail = tail->next;
tail->next = new;
}
return (new);
}
void free_path_list(list_path **head)
{
list_path *temp, *curr;
/*printf("free is called\n"); */
if (head != NULL)
{
curr = *head;
while ((temp = curr) != NULL)
{
curr = curr->next;
free(temp);
}
*head = NULL;
}
}
