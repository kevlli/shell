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
  int f, status;
  int p = getpid();
  printf("$ ");
  while (p == getpid()) {
    int i = fork();
    if (i) {
      f = wait(&status);
      //printf("%s\n", buffer);
    }
    else {
      fgets(buffer, sizeof(buffer) - 1, stdin);
      //printf("%s\n", buffer);

      int c = 0;
      int status = 0;
      while (buffer[c] != '\n') {
        if (buffer[c] == ';') status = 1;
        c++;
      }
      buffer[c] = 0;
      if (status == 1) {
        char **cmds;
        char *curr = buffer;
        char *token;
        c = 0;
        while (curr) {
          token = strsep(&curr, ";");
          cmds[c] = token;
          c++;
        }
        execute_multiple(parse_cmd(cmds[0]),parse_cmd(cmds[1]));
        return 0;
      }
      execute_cmd(parse_cmd(buffer));
    }
  }
  return 0;
}

char** parse_cmd(char *line) {
    int i = 0;
    char **args;
    args = malloc(sizeof(char *) * 5);
    char *curr = line;
    char *token;
    //printf("a\n");

    while (curr) {
      token = strsep(&curr, " ");
      args[i] = token;
      //printf("Argument %d: %s\n", i+1, token);
      i++;
    }

    if (i > 5) args = realloc(args, sizeof(char *) * i);

    if (!strcmp(args[0],"cd")) {
      change_dir(args[1]);
      return 0;
    }
    return args;
}
