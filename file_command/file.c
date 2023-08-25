#include "shell.h"
/**
 * execute_commands_from_file - executes commands from a file
 * @filename: the name of the file containing commands
 *
 * Return: the exit status of the last executed command
 */
int execute_commands_from_file(char *filename)
{
ali_t *ali_list = NULL;
    char *line = NULL, **argv, *newline, *token;
    size_t len = 0;
    ssize_t nread = 0;
    int exit_status = 0, is_builtin = 1, argc;
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        perror("File Error");
        exit(EXIT_FAILURE);
    }
    while ((nread = getline(&line, &len, file)) != -1)
    {
        newline = strchr(line, '\n');
        if (newline)
            *newline = '\0';
        token = strtok(line, "\n");
        while (token != NULL)
        {
            argv = process_line(token, &argc);
            if (argc != 0)
            {
                is_builtin = execute_builtin(token, argv, 0, &exit_status, &ali_list);
                if (is_builtin == 1)
                    exit_status = exe(argv, 0, &ali_list);
                free_array(argv);
            }
            token = strtok(NULL, "\n");
        }
    }
    fclose(file);
    cleanup(&ali_list, env_copy, line);
    return (exit_status);
}
