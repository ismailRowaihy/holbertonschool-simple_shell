#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include "shell.h"
#include <fcntl.h>
/**
 *
 *
 *
 */

int main(void)
{
	pid_t my_son_pid;
	char *line = NULL;
	size_t n = 0;
	ssize_t nread;
	char *args[64];
	char *path = NULL;
	char fullpath[124];
	char *dir;
	int i , is_path;
	int status = 0;

	while (1)
	{

		if (isatty(STDIN_FILENO))
			printf("($) ");


		nread = getline(&line, &n, stdin);
		if (nread == -1)
			break;

		if (only_spaces(line))
			continue;


		input_tok(line, args);


		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			exit(0);
		}

		if (args[0] == NULL)
			continue;

		is_path = (args[0][0] == '/' ||
                       strncmp(args[0], "./", 2) == 0 ||
                       strncmp(args[0], "../", 3) == 0);
		

		if (!is_path)
		{
			for (i = 0; environ[i] != NULL; i++)
			{
				if (strncmp(environ[i], "PATH=", 5) == 0)
				{
					path = strdup(environ[i] + 5);
					break;
				}
			}

			if (!path)
			{
				status = 127;
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				continue;
			}


			dir = strtok(path, ":");

			while (dir != NULL)
			{
				if (strlen(dir) + strlen(args[0]) + 2 >= sizeof(fullpath))
				{
					dir = strtok(NULL, ":");
					continue;
				}
				strcpy(fullpath, dir);
				strcat(fullpath, "/");
				strcat(fullpath, args[0]);
				if (access(fullpath, X_OK) == 0)
				{
					args[0] = fullpath;
					break;
				}
				dir = strtok(NULL, ":");
			}

			if (dir == NULL)
			{
				fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
				free(path);
				status = 127;
				continue;
			}

			
				free(path);
				path = NULL;
			

		}
		if (access(args[0], X_OK) == 0)
		{
			my_son_pid = fork();
			file_exec(my_son_pid, args);
		}
		else
		  {
		    fprintf(stderr, "./hsh: 1: %s: not found\n", args[0]);
            status = 127;
		  }
	}

	free(line);
	return (status);
}
