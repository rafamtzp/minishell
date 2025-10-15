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
void handle_err(int errnum, int err, char *msg)
{
	if (err == 1)
		printf("cd: %s: %s\n", strerror(errno), msg); // handle_err()
	else
		perror("Error");
	return ;
}

void cd(char *path)
{
	if (chdir(path) != 0)
		handle_err(errno, 1, "filename");
}

void pwd(void)
{
	char *buf;

	buf = ft_calloc(1, PATH_MAX);
	if (!buf)
		handle_err(errno, 2, "");
	printf("%s\n", getcwd(buf, PATH_MAX));
}

void export(t_envar *envar)
{
	return ;
}