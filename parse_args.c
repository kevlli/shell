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
  int e = execvp(line[0], line);
  if (e == -1) printf("%s\n", strerror(errno));
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

// void execute_multiple_test(char **line) {
//   int i, c, f, status;
//   char **cmd = line;
//   while (cmd) {
//     cmd = parse_cmd(line[i]);
//     i++;
//
//     c = fork();
//     if (i) f = wait(&status);
//     else execute_cmd(cmd);
//   }
// }

void redirect_out(char **line, int i) {
  char **cmd = parse_cmd(line[0]);
  char *n = parse_cmd(line[1])[0];
  int fd1;
  if (i) fd1 = open(n, O_WRONLY | O_APPEND | O_CREAT, 0644);
  else fd1 = open(n, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  int backup_stdout = dup(STDOUT_FILENUM);
  dup2(fd1, STDOUT_FILENUM);
  execvp(cmd[0], cmd);
  dup2(backup_stdout, STDOUT_FILENUM);
  printf(">\n");
  close(fd1);
}

void redirect_in(char **line) {
  char **cmd = parse_cmd(line[0]);
  int fd1 = open(parse_cmd(line[1])[0], O_RDONLY); //changed to RDONLY
  int backup_stdin = dup(STDIN_FILENUM);
  dup2(fd1, STDIN_FILENUM);
  execvp(cmd[0], cmd);
  dup2(backup_stdin, STDIN_FILENUM);
}

void simple_pipe(char ** line) { //need to remove extra spaces from commands
  FILE *pipein_fp, *pipeout_fp;
  char readbuf[80];
  char *cmd = line[0];
  remove_whitespace(cmd);
  char *cmd2 = line[1];
  remove_whitespace(cmd2);
  pipein_fp = popen(cmd, "r");
  pipeout_fp = popen(cmd2, "w");
  while (fgets(readbuf, 80, pipein_fp) != NULL) {
  	fputs(readbuf, pipeout_fp);
  }
  pclose(pipein_fp);
  pclose(pipeout_fp);
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

char* remove_whitespace(char *str) {
  int len = 0;
  int i = 0;
  while (str[i]) {
    len++;
    i++;
  }
  while (str[i] == ' ') {
    str[i] = 0;
    i--;
  }
  i = 0;
  while (str[i] == ' ') {
    i++;
    str++;
  }
  return str;
}
