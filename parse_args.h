void execute_cmd(char **line);
void execute_multiple(char **a, char **b);

// void execute_multiple_test(char **line);
char** parse_cmd(char *line);
void redirect_out(char **line, int i);
void redirect_in(char **line);
void simple_pipe(char ** line);
