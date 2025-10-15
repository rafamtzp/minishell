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

void print_alphabetically(t_envar *envar)
{
	int i;
	int size;
	t_envar *head;

	head = envar;
	size = env_lstsize(head);
	i = 0;
	while (i < size)
	{
		envar = head;
		while (envar->ascii_index != i)
			envar = envar->next;
		printf("%s=%s\n", envar->varname, envar->value);
		i++;
	}
}

void write_envars(t_envar *envar, bool order_alpha)
{
	if (order_alpha == true)
		print_alphabetically(envar);
	else
	{
		while (envar != NULL)
		{
			printf("%s=%s\n", envar->varname, envar->value);
			envar = envar->next;
		}
	}
}

void	add_envars(t_envar **envar, char **cmd)
{
	t_envar *node;

	// add the variables
	
	// update their alphabetical index
	update_env_indexes(envar);
}

void export(t_envar **envars, char **cmd)
{
	if (count_args(cmd) == 0) // TODO
		write_envars(*envars, true); //
	else
		add_envars(envars, cmd);
}