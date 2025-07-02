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
  char *relBUFFER = "/bin/";

  while(1)
    {   
      if(isatty(STDIN_FILENO))
	printf("($) ");
      
      nread = getline(&line,&n,stdin);
      if( nread == -1 )
        break;
      
      input_tok(line,args);
      if (args[0] == NULL)
	continue;


      if (strcmp(args[0], "exit") == 0)
	  exit(0);      

      if (args[0][0] != '/')
	{
	  relBUFFER = "/bin/";
	  strcat(relBUFFER,args[0]);
	  printf("%s\n",relBUFFER);
	}

      if(relBUFFER = "")
	relBUFFER = args[0];
	
      if(access(relBUFFER,F_OK) == 0)
	{
	  relBUFFER = "";
	  my_son_pid = fork();
	  file_exec(my_son_pid,args);
	}
      else
	printf("the file is not correct");  
      
    }
  free(line);
  return (0);
}
