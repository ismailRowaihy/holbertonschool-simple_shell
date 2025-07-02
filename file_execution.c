#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void file_exec(pid_t my_son_pid, char **args)
{

//extern char **environ;

  if (my_son_pid ==  0)
	{
      
	  if(execvp(args[0],args) == -1)
	    {
	    exit(EXIT_FAILURE);
	    }
	}
      else
	{
	  wait(&my_son_pid);
	}        
}
