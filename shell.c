#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "parse_args.h"
#include "shell.h"

int main() {
  char buffer[255];
  char path[100];
  int f, status;
  int p = getpid();
  while (p == getpid()) {
    printf("%s", getcwd(path, 100));
    printf("$ ");
    fgets(buffer, sizeof(buffer) - 1, stdin);

    int c = 0;
    int s = 0;
    while (buffer[c] != '\n') {
      if (buffer[c] == ';') s = 1;
      if (buffer[c] == '>') {
        if (buffer[c+1] == '>') {
          s = 3;
        }
          s = 2;
      }
      if (buffer[c] == '<') s = 3;
      c++;
    }
    buffer[c] = 0;

    int i = fork();
    if (i) {
      f = wait(&status);

      if (WEXITSTATUS(status) == 1) chdir(parse_cmd(buffer)[1]);
      if (WEXITSTATUS(status) == 2) kill(getpid(), 2);
    }
    else {
      if (s == 1) {
        char **cmds = seperate_cmds(buffer, ';');
        execute_multiple(parse_cmd(cmds[0]),parse_cmd(cmds[1]));
        free(cmds);
        return 0;
      }
      else if (s == 2) {
        char **cmds = seperate_cmds(buffer, '>');
        redirect_out(cmds);
        return 0;
      }
      else if (s == 3) {
        char **cmds = seperate_cmds(buffer, '>'); //need to figure out a way to distringuish
        redirect_out(cmds);
        return 0;
      }

      char** args = parse_cmd(buffer);
      if (strcmp(args[0],"cd") == 0) {
        return 1;
      }

      if (strcmp(args[0],"exit") == 0) {
        return 2;
      }

      execute_cmd(args);
    }
  }
  return 0;
}

char** seperate_cmds(char *line, char sep) {
  char **cmds = malloc(8 * sizeof(char*));
  char *curr = line;
  char *token;
  int c = 0;
  while (curr) {
    token = strsep(&curr, &sep);
    cmds[c] = token;
    c++;
  }
  if (c > 8) cmds = realloc(cmds, sizeof(char *) * c);
  return cmds;
}
