#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

void input_tok(char *line,char **args){
  int i;
  char *tokens;
line[strcspn(line,"\n")] = 0;

tokens =strtok(line," ");
  i = 0;
while(tokens)
{
args[i] = tokens;

tokens = strtok(NULL," ");
i++;
}
args[i] = NULL;
}


