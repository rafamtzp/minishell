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

void env(t_envar **envars)
{
	write_envars(*envars, true);
}

void	del_env(t_envar **ptr1, t_envar **ptr2, t_envar **ptr3, bool ishead)
{
	if (ishead == true)
	{
		free_env_content(*ptr1);
		*ptr1 = (*ptr1)->next;
		free(ptr2);
		*ptr2 = *ptr1;
	}
	else
	{
		free_env_content(*ptr1);
		*ptr3 = *ptr1;
		*ptr1 = (*ptr1)->next;
		free(*ptr3);
		(*ptr2)->next = *ptr1;
	}
}

void unset(t_envar **envars, char **cmd)
{
	int i;
	t_envar *ptr1;
	t_envar *ptr2;
	t_envar *ptr3;

	i = 1;
	ptr1 = *envars;
	ptr2 = *envars;
	while (cmd[i] != NULL)
	{
		while (ptr1->varname != cmd[i])
		{
			ptr1 = ptr1->next;
			if (ptr1->varname != cmd[i])
				ptr2 = ptr2->next;
		}
		if (ptr1 == *envars)
		{
			*envars = (*envars)->next;
			del_env(&ptr1, &ptr2, &ptr3, true);
		}
		else
			del_env(&ptr1, &ptr2, &ptr3, false);  // Not sure if this logic checks out....
	}
}

void michi_exit(void)
{
	// TODO
	return ;
}


// reminder: look into getenv and remaining ones!!!!