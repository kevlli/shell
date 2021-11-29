# project01
## Shell Project
### Features:
Runs terminal commands  
Supports commands separated by ';'  
Redirects stdout (with '>' and '>>')  
Redirects stdin (with '<')
Supports piping  
Runs commands with leading or trailing spaces  
### Abandoned Features:
Running more than 2 commands at the same time with semicolons  
### Bugs / Info:
Only run redirection / semicolons / piping one at a time  
Cd and exit doesn't run inside '>', '<', ';', '|'
Running ls for a nonexistent file exits shell
### Functions Headers:
char** seperate_cmds(char *line, char sep);
int read_cmd(char *line);
void execute_cmd(char **line);
void execute_multiple(char **a, char **b);
char** parse_cmd(char *line);
void redirect_out(char **line, int i);
void redirect_in(char **line);
void simple_pipe(char ** line);
char* remove_whitespace(char *str);
