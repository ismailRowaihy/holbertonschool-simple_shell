#ifndef SHELL_H
#define SHELL_H

extern char **environ;

void file_exec(pid_t my_son_pid, char **args);
void input_tok(char *line, char **args);
int only_spaces(char *s);

#endif
