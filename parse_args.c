#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "parse_args.h"

// TODO:
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

void change_dir(char *line) { // cd does not change shell's directory. needs fixing
  chdir(line);
  // printf("%s\n",line);
  // printf("%s\n",getcwd(s, 100));
}
