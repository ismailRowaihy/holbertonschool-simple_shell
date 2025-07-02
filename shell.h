#ifndef SHELL_H
#define SHELL_H

void file_exec(pid_t my_son_pid,char **args);
void input_tok(char *line, char *tokens, char **args);
#endif
