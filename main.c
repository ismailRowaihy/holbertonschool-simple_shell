#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 *
 *
 *
 */
int main(void)
{
  pid_t my_pid,my_son_pid,my_ppid;
  char *line = NULL;
  size_t n = 0;
  ssize_t nread;
  //  char *args[];
  
  my_son_pid = fork();

if (my_son_pid != 0)
    wait(&my_son_pid);

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
     if (my_son_pid ==  0)
       {
	 //args[]={"/bin/", "",NULL};
	 if(execve("/bin/ls",&line,NULL) == -1)
	   perror("failedx");
       }
     else
       {
	 printf("hi kid im dad");
       }
     
     printf("%s",line);
   }
 free(line);
 return (0);
}
