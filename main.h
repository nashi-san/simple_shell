#ifndef MAIN_H
#define MAIN_H
extern char **environ;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define INITIAL_BUF_SIZE 1024

/**
* struct list_path - singly linked list
* @str: string - (malloc'ed string)
* @next: points to the next node
*
* Description: singly linked list node structure
*/
typedef struct list_path
{
char *str;
struct list_path *next;
} list_path;

void loop(void);
list_path *load_path(void);
void process_input(list_path *dirs, char *line);
int valid_command(const char *value);
void execute_command(const char *full_command, char *const argv[]);
void exit_command(char *line);

void printenv(void);
char *_getenv(const char *name);
list_path *add_node_end(list_path **head, const char *value);
void free_path_list(list_path **head);

int compare_path_lists(list_path *list1, list_path *list2);
list_path *duplicate_path_list(list_path *orig);


int _strcmp(const char *s1, const char *s2);








#endif
