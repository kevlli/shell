#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include "parse_args.h"

// TODO: cd, exit, recieve input, check for semicolon

void cd(char *line);

// int main() {
//   char cmd[] = "ls -a -l -d -b -i";
//   char cmd[] = "cd fake";
//   execute(cmd);
//   return 0;
// }


void execute_cmd(char *line) {

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
  
  if ( !strcmp(args[0],"cd") ) {
    cd(args[1]);
    return;
  }
  
  if (i > 5) args = realloc(args, sizeof(char *) * i);
  execvp(args[0], args);
  free(args);
}


void cd(char *line) { // cd does not change shell's directory. needs fixing
  int a = chdir(line);
  printf("%s\n",strerror(a));
}
