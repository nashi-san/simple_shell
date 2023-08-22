#ifndef SHELL_H
#define SHELL_H

/*libraries*/
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

/*globalvar*/
extern char **environ;

/*buffermacro*/
#define BUF_SIZE 64

/*struct*/
/**
 * struct builtin - ..
 * @name: ..
 * @function: ..
 */
struct builtin
{
        char *name;
        int (*function)(char *line, char **argv, int n, int *exit_status);
};

typedef struct builtin builtin_t;

/*funcs_core*/
int exe(char **argv, int n);
void handle_comment(char *line);
char **process_line(char *line, int *argc);
int execute_builtin(char *line, char **argv, int n, int *exit_status);
int execute_command(char **argv, char *path);

/*funcs_mem*/
void free_array(char **argv);
char *_memcpy(char *dest, char *src, unsigned int m);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/*funcs_str*/
char *n_conversion(int n);
int _strlen(char *str);
int _strcmp(char *s1, char *s2);
int _atoi(char *s);

/*funcs_built-ins*/
int env_builtin(char *line, char **argv, int n, int *exit_status);
int exit_builtin(char *line, char **argv, int n, int *exit_status);
                                                                                                                                                                                                                                     /*funcs_custom*/
char *_which(char *command);
/* my_strtok*/
char *_strtok(char *str, const char *delimiters);
/* my_getline*/
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t read_line(char *buffer);
/*funcs_print*/
void err_msg_cmd(char **argv, int n);
void err_msg_exit(char *status, int n);
int _putchar(char c);
int _puts_stderr(char *s);
void _puts_stdout(char *str);

#endif