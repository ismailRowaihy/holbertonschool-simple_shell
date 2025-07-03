#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

int file_exec(pid_t my_son_pid, char **args)
{
  int status;  

  if (my_son_pid ==  0)
	{

		if (execve(args[0], args, environ) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
	  waitpid(my_son_pid, &status, 0);

	  if (WIFEXITED(status))
	    {
	      return (WEXITSTATUS(status));
	    }
	  
	}
  return (0);
}
