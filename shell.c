#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
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

    int s = read_cmd(buffer);
    // char **fun;
    int i = fork();
    if (i) {
      f = wait(&status);

      if (WEXITSTATUS(status) == 1) {
        int error = chdir(parse_cmd(buffer)[1]);
        if (error == -1) printf("%s\n", strerror(errno));
      }
      if (WEXITSTATUS(status) == 2) exit(0);
      // if (WEXITSTATUS(status) == 3) {
      //   fun = seperate_cmds(buffer, ';');
      //   char **a = parse_cmd(fun[0]);
      //   char **b = parse_cmd(fun[1]);
      //   if (strcmp(a[0], "cd") == 0) chdir(a[1]);
      // }
    }
    else {
      char **cmds;
      if (s == 1) {
        cmds = seperate_cmds(buffer, ';');
        execute_multiple(parse_cmd(cmds[0]),parse_cmd(cmds[1]));
        //execute_multiple_test(cmds);
        free(cmds);
        return 0;
      }
      else if (s == 2) {
        cmds = seperate_cmds(buffer, '>');
        redirect_out(cmds, 0);
        free(cmds);
        return 0;
      }
      else if (s == 3) {
        cmds = seperate_cmds(buffer, '>'); //need to figure out a way to distringuish
        redirect_out(cmds, 1);
        free(cmds);
        return 0;
      }
      else if (s == 4) {
        cmds = seperate_cmds(buffer, '<');
        redirect_in(cmds);
        free(cmds);
        return 0;
      }
      else if (s == 5) {
        cmds = seperate_cmds(buffer, '|');


        free(cmds);
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

int read_cmd(char *line) {
  int c = 0;
  int s = 0;
  while (line[c] != '\n') {
    if (line[c] == ';') s = 1;
    if (line[c] == '>') {
      if (line[c+1] == '>') {
        s = 3;
        c++;
      }
      else s = 2;
      c++;
    }
    if (line[c] == '<') s = 4;
    if (line[c] == '|') s = 5;
    c++;
  }
  line[c] = 0;
  return s;
}

char** seperate_cmds(char *line, char sep) {
  char **cmds = malloc(8 * sizeof(char*));
  char *curr = line;
  char *token;
  int c = 0;
  while (curr) {
    token = strsep(&curr, &sep);
    if (strcmp(token, "")) cmds[c] = token;
    else c--;
    c++;
  }
  if (c > 8) cmds = realloc(cmds, sizeof(char *) * c);
  return cmds;
}
