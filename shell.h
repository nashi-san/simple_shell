#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

#define BUF_SIZE 128
/**
 * struct ali - aliases linked list.
 * @name: the alias name.
 * @value: the alias value.
 * @next: a pointer to next element.
 */

typedef struct ali
{
	char *name;
	char *value;
	struct ali *next;
} ali_t;


/*struct*/
/**
 * struct builtin - built-ins names and functions
 * @name: built-in name
 * @function: built-in function
 */
struct builtin
{
	char *name;
	int (*function)(char *line, char **argv, int n, int *exit_status,
	ali_t **ali_list);
};
typedef struct builtin builtin_t;


/*funcs_core*/
int exe(char **argv, int n, ali_t **ali_list);
void handle_comment(char *line);
char **process_line(char *line, int *argc);
int execute_builtin(char *line, char **argv, int n, int *exit_status,
ali_t **ali_list);
int execute_command(char **argv, char *path);

/*funcs_mem*/
void free_array(char **argv);
void free_aliases(ali_t **ali_list);
char *_memcpy(char *dest, const char *src, unsigned int m);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void cleanup(ali_t **ali_list, char **env_copy, char *line);

/*funcs_str1*/
char *_strchr(char *s, char c);
char *n_conversion(int n);
int _strlen(const char *str);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

/*funcs_str2*/
int _strncmp(const char *s1, const char *s2, size_t n);
int _isdigit(int c);
char *_strdup(const char *str);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);

/*funcs_built-ins*/
int env_builtin(char *line, char **argv, int n,
		int *exit_status, ali_t **ali_list);
int exit_builtin(char *line, char **argv, int n,
		int *exit_status, ali_t **ali_list);
int cd_builtin(char *line, char **argv, int n,
		int *exit_status, ali_t **ali_list);
void cd_update_env(void);

/*funcs_alias*/
int alias_builtin(char *line, char **argv, int n,
		int *exit_status, ali_t **ali_list);
void print_alias(ali_t *ali_list);
void print_single_alias(char *alias_name, ali_t *ali_list);
void update_alias(char *alias_name, char *alias_value,
		ali_t **ali_list);
void create_alias(char *alias_name, char *alias_value, ali_t **ali_list);
char *find_alias(char *alias_name, ali_t **ali_list);

/*funcs_env*/
char **env_copy;
int setenv_builtin(char *line, char **argv, int n,
		int *exit_status, ali_t **ali_list);
int _setenv(char *variable, char *value);
int unsetenv_builtin(char *line, char **argv, int n,
		int *exit_status, ali_t **ali_list);
int _unsetenv(char *variable);
void copy_environ(void);

/*funcs_custom*/
char *_which(char *command);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int _getchar(void);
char *_strtok(char *str, char *delimiters);
char *_getenv(char *variable);

/*funcs_errmsgs*/
void err_msg_cmd(char **argv, int n);
void err_msg_exit(char *status, int n);
void err_msg_cd(char **argv, int n);

/*funcs_print*/
int _putchar(char c);
int _puts_stderr(char *s);
void _puts_stdout(char *str);

#endif
