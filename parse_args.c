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
