#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 *
 *
 *
 */
int main(void)
{
  pid_t my_son_pid;
  char *line = NULL;
  size_t n = 0, i;
  ssize_t nread;
  char *args[64];
  extern char **environ;
  char *tokens;
  const char *deli = " ";
  
  while(1)
    {   
      if(isatty(STDIN_FILENO))
	printf("($) ");
   
      nread = getline(&line,&n,stdin);
      if( nread == -1 )
	{
	  printf("error");
	  break;
	}
      line[strcspn(line,"\n")] = 0;
      
      tokens =strtok(line,deli);
      
      i = 0;
      while(tokens)
      {
       args[i] = tokens;
     tokens = strtok(NULL, deli);
      i++;
      }
      
      args[i] = NULL;

      if (args[0] == NULL)
	continue;

      
      
      my_son_pid = fork();
     
      if (my_son_pid ==  0)
	{
	  
	  if(execve(args[0],args,environ) == -1)
	    perror("failedx");
	  
	  return (0);
	}
      else
	{
	  wait(&my_son_pid);
	}
      free(line);
      
    }
  free(line);
  return (0);
}
