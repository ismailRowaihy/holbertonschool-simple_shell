#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include "shell.h"

/**
 *
 *
 *
 */
int main(void)
{
  pid_t my_son_pid;
  char *line = NULL;
  size_t n = 0,i = 0;
  ssize_t nread;
  char *args[64];
  char *tokens;
struct stat st;
  
  while(1)
    {   
      if(isatty(STDIN_FILENO))
	printf("($) ");
   
      nread = getline(&line,&n,stdin);
      if( nread == -1 )
        break;
      
input_tok(line,tokens,args);

if (args[0] == NULL)
  continue;


if(stat(args[0], &st) == 0)
{
my_son_pid = fork();
file_exec(my_son_pid,args);
}
else
printf("the path is not correct");  
}
free(line);
  return (0);
}
