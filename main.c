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
  while(1)
    {

     if(isatty(STDIN_FILENO))
	printf("($) ");


      nread = getline(&line,&n,stdin);
      if( nread == -1 )
        break;

      input_tok(line,args);



                if (strcmp(args[0], "exit") == 0)
                {
free(line);
                        exit(0);
                }


      if (args[0] == NULL)
	continue;



  if(args[0][0] != '/')
{
abs_path = malloc(strlen("/bin/") + strlen(args[0]) + 1);



if(abs_path == NULL)
{
perror("malloc failed");
exit(0);
}
strcpy(abs_path,"/bin/");
strcat(abs_path,args[0]);
args[0] = abs_path;
}


      if(access(args[0],F_OK) == 0)
	{


 my_son_pid = fork();

	 
	  file_exec(my_son_pid,args);
	}
      else
{
if(args[0][0] == '/')
free(args[0]);
free(line);
              exit(0);
}
   }
if(args[0][0] == '/')
free(args[0]);
free(line);
  return (0);
}
