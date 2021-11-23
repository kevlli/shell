#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "parse_args.h"

#define STDIN_FILENUM 0
#define STDOUT_FILENUM 1

// TODO: redirection, piping
void execute_cmd(char **line) {
  execvp(line[0], line);
  free(line);
}

void execute_multiple(char **a, char **b) {
  int i = fork();
  int f, status;
  if (i) {
    f = wait(&status);
    execute_cmd(b);
  }
  else {
    execute_cmd(a);
  }
}

void redirect_out(char **line) {
  char **cmd = parse_cmd(line[0]);
  int fd1 = open(parse_cmd(line[1])[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
  int backup_stdout = dup(STDOUT_FILENUM);
  dup2(fd1, STDOUT_FILENUM);
  execvp(cmd[0], cmd);
  dup2(backup_stdout, STDOUT_FILENUM);
}

void redirect_in(char **line) {

}

char** parse_cmd(char *line) {
    int i = 0;
    char **args;
    args = malloc(sizeof(char *) * 5);
    char *curr = line;
    char *token;

    while (curr) {
      token = strsep(&curr, " ");
      if (strcmp(token, "")) args[i] = token;
      else i--;
      //printf("Argument %d: %s\n", i+1, token);
      i++;
    }

    if (i > 5) args = realloc(args, sizeof(char *) * i);
    return args;
}
