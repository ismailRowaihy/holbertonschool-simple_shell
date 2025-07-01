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
  pid_t my_pid,my_son_pid,my_ppid;
  char *line = NULL;
  size_t n = 0, i;
  ssize_t nread;
  char *args[64];
  //char *args[3] = {"/bin/ls","-l",NULL};
  //extern char **environ;
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
      printf("at index %ld there is %s\n",i,args[i]);
     tokens = strtok(NULL, deli);
      i++;
      }
      
      args[i] = NULL;

      if (args[0] == NULL)
	continue;

      
      
      my_son_pid = fork();
     
      if (my_son_pid ==  0)
	{
	  printf("im the kid");
	  if(execvp(args[0],args) == -1)
	    perror("failedx");
	  printf("after exec");
	  return (0);
	}
      else
	{
	  printf("before %d \n",my_son_pid);
	  wait(&my_son_pid);
	  printf("affter %d \n",my_son_pid);
	  printf("hi kid im dad");
	}
     
      printf("%s",line);
      free(line);
      
    }
  free(line);
  return (0);
}
