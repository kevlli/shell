#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "parse_args.h"

int main() {
  char buffer[255];
  int f, status;
  int p = getpid();
  printf("$ ");
  while (p == getpid()) {
    int i = fork();
    if (i) {
      f = wait(&status);
    }
    else {
      fgets(buffer, sizeof(buffer) - 1, stdin);
      //printf("%s\n", buffer);

      int c = 0;
      while (buffer[c] != '\n') {
        c++;
      }
      buffer[c] = 0;
      parse_cmd(buffer);
    }
  }
}
