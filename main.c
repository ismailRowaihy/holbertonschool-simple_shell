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
  char *abs_path;
  char *env ;
char *path;
char *fullpath[64];
char *dir;
char *tmp;
extern char **environ;
  while(1)
    {

     if(isatty(STDIN_FILENO))
	printf("($) ");


      nread = getline(&line,&n,stdin);
            if( nread == -1 )
              break;
          if(nread == 1)
              continue;


input_tok(line,args);


      if (strcmp(args[0], "exit") == 0)
	{
	  free(line);
	  exit(0);
	}





if (args[0] == NULL)
	continue;


if(access(args[0] ,F_OK) != 0)
{
        env = getenv("PATH");
        path = strdup(env);
        dir = strtok(path,":");
fullpath[0] = malloc(strlen(dir) + strlen(args[0]) + 2);
if(fullpath[0] == NULL)
return(0);
while(dir != NULL)
{
strcpy(fullpath[0],dir);
strcat(fullpath[0],"/");
strcat(fullpath[0],args[0]);
if(access(fullpath[0],X_OK) == 0)
{
args[0] =fullpath[0];
break;
}
dir = strtok(NULL,":");

tmp = realloc(fullpath[0],strlen(dir) + strlen(args[0]) + 1);
if(tmp == NULL)
free(fullpath[0]);
fullpath[0] = tmp;
}

}
if(access(args[0],X_OK) == 0)
{
my_son_pid = fork();
file_exec(my_son_pid,args);
}
}
free(fullpath[0]); 
 free(line);
  return (0);

}
