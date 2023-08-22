#include "main.h"
int compare_path_lists(list_path *list1, list_path *list2)
{
	list_path *node1 = list1;
	list_path *node2 = list2;

	while (node1 != NULL && node2 != NULL)
	{
		if (_strcmp(node1->str, node2->str) != 0)
			return (-1);
		node1 = node1->next;
		node2 = node2->next;
	}
	if (node1 == NULL && node2 == NULL)
		return (0);
	return (-1);
}
list_path *duplicate_path_list(list_path *orig)
{
	list_path *new_list = NULL, *new_node = NULL, *last = NULL;
	list_path *current = orig;

	while (current != NULL)
	{
		new_node = (list_path *)malloc(sizeof(list_path));
		if (new_node == NULL)
		{
			exit(EXIT_FAILURE);
		}
		new_node->str = strdup(current->str);
		new_node->next = NULL;
		if (new_list == NULL)
		{
			new_list = new_node;
		}
		else
		{
			last = new_list;
			while (last->next != NULL)
			{
				last = last->next;
			}
			last->next = new_node;
		}
		current = current->next;
	}
	return (new_list);
}
