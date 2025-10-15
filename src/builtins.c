#include "minishell.h"

void echo(char *msg, bool newline)
{
	if (newline == true)
		printf("%s\n", msg);
	else
		printf("%s", msg);
}
/*
Note: cd should change the working directory of a process!!!
But, it doesn't change the working directory of the current shell.
Because when the program is executed in the shell, 
the shell follows fork on exec mechanism. 
So, it doesn't affect the current shell. 
*/

void cd(char *path)
{
	if (chdir(path) != 0)
		perror()
}