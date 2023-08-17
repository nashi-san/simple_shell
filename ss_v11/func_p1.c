#include "main.h"

void loop(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	list_path *dirs = NULL; 	

	if (dirs == NULL)
		dirs = load_path();	

	printf("$ ");	
	while ((nread = getline(&line, &len, stdin)) != -1)
	{
		process_input(dirs, line);
		printf("$ ");
		free(line);
		line = NULL;
		len = 0;
	}
	free_path_list(&dirs);
}
list_path *load_path(void)
{
	list_path *head = NULL;
	char *env_value, *env_copy, *dir, *dir_path;

	env_value = _getenv("PATH");
	if (env_value == NULL)
		return (head);
	env_copy = strdup(env_value);
	if (env_copy == NULL)
	{
		free(env_value);
		return (NULL);
	}
	dir = strtok(env_copy, ":");
	while (dir != NULL)
	{
		dir_path = malloc(strlen(dir) + 2);
		if (dir_path == NULL)
		{
			free(dir);
			free(env_copy);
			free(env_value);
			free_path_list(&head);
			return (NULL);
		}
		strcpy(dir_path, dir);
		strcat(dir_path, "/");
		if (add_node_end(&head, dir_path) == NULL)
		{
			free(dir_path);
			free(dir);
			free(env_copy);
			free(env_value);
			free_path_list(&head);
			return (NULL);
		}
		dir = strtok(NULL, ":");
	}
	free(env_copy);
	free(env_value);
	return (head);
}

void process_input(list_path *dirs, char *line)
{
	char *argv[INITIAL_BUF_SIZE], *full_command;
	list_path *current;
	size_t full_command_len;
	int argc = 0;

	argv[argc] = strtok(line, " \n");
	while (argv[argc] != NULL && argc < INITIAL_BUF_SIZE - 1)
	{
		argc++;
		argv[argc] = strtok(NULL, " \n");
	}
	if (argv[0] == NULL)
	{
		return;
	}
	if (_strcmp(argv[0], "exit") == 0)
	{
		exit_command(argv[1]);
	}
	if (_strcmp(argv[0], "env") == 0)
	{
		printenv();
		return;
	}
	/*	if (valid_command(argv[0]) == 0)*/
	/*	{*/
	/*		full_command = argv[0];*/
	/*		execute_command(full_command, argv); */
	/*		return;*/
	/*	}*/
	current = dirs;
	while (current != NULL)
	{
		full_command_len = strlen(current->str) + strlen(argv[0]) + 1;
		full_command = malloc(full_command_len);
		if (full_command == NULL)
			exit(EXIT_FAILURE);
		strcpy(full_command, current->str);
		strcat(full_command, argv[0]);
		if (access(full_command, X_OK) == 0)
		{
			execute_command(full_command, argv);
			free(full_command);
			break;
		}
		free(full_command);
		current = current->next;
	}
	if (current == NULL)
	{
		printf("%s: command not found\n", argv[0]);
		return;
	}
}
void execute_command(const char *full_command, char *const argv[])
{
	int exit_status;
	pid_t childpid = fork();

	if (childpid == -1)
	{
		perror("Error:");
		exit(1);
	}
	if (childpid == 0)
	{
		if (execve(full_command, argv, environ) == -1)
		{
			perror("Error:");
			exit(1);
		}
	}
	else
	{
		wait(&exit_status);
	}
}
void exit_command(char *argv)
{
	if (argv != NULL)
	{
		exit(atoi(argv));
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}
