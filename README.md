# project01
## Shell Project
### Features:
Runs all terminal commands with unlimited arguments    
Supports running multiple commands on one line `;`  
Redirects stdout `>` and `>>`  
Redirects stdin `<`  
Supports piping `|`  
Runs commands with leading or trailing spaces  
### Abandoned Features:
Running more than 2 commands in operators `> >> ; | <`    
Running cd or exit from commands in operators `> >> ; | <`  
### Bugs / Info:
Cd doesn't run inside operators `> >> | <`  
Exit doesn't run inside operators `> >> ; | <`   
Can't handle more than two commands seperated by operators `> >> ; | <`  
Buffer size is 255 characters large  
Running ls for a nonexistent file exits shell
### Function Headers:
#### shell.c
**char\*\* seperate_cmds(char \*line, char sep);**\
Seperates a line into commands by a given operator  
**int read_cmd(char \*line);**\
Looks through commands for special operator and returns an int dependent on which operator is present    
#### parse_args.c
**void execute_cmd(char \*\*line);**\
Executes a given command  
**void execute_multiple(char \*\*a, char \*\*b);**\
Executes multiple commands when `;` operator is given  
**char\*\* parse_cmd(char \*line);**\
Seperates a command into arguments  
**void redirect_out(char \*\*line, int i);**\
Redirects stdout when `>` or `>>` operator is given  
**void redirect_in(char \*\*line);**\
Redirects stdin when `<` operator is given  
**void simple_pipe(char \*\* line);**\
Handles piping when `|` operator is given  
**char\* remove_whitespace(char \*str);**\
Helper function for **simple_pipe**, removes whitespace from commands for piping  
