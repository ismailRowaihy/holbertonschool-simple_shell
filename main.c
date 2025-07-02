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
  size_t n = 0,i = 0;
  ssize_t nread;
  char *args[64];
  char *tokens;
  struct stat st;
  int path;

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


      if (strcmp(args[0], "exit") == 0)
	  exit(0);

      path = open("/bin/",O_DIRECTORY);
      if (path == -1)
	perror("failed to open the file");


 if(faccessat(path,args[0], F_OK , 0) != -1)
   {
     close(path);
     my_son_pid = fork();
     file_exec(my_son_pid,args);
   }
 else
   printf("the file is not correct");  
 
    }
  free(line);
  return (0);
}
