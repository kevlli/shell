#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include "parse_args.c"

int main() {
  char buffer[255];
  int f, status;
  while (1) {
    printf("$ ");
    fgets(buffer, sizeof(buffer) - 1, stdin);
    int i = fork();
    if (i) {
      execute(buffer);
    }
    else {
      f = wait(&status);
    }
  }
}
