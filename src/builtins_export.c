#include "minishell.h"

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
		printf("declare -x %s=\"%s\"\n", envar->varname, envar->value);
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

void	add_envars(t_envar **envars, char **cmd)
{
	t_envar *new;
	int i;

	// assume params have format name=value
	i = 1;
	while (cmd[i] != NULL)
	{
		new = envlst_new(envars, cmd[i]);
		if (!new)
			handle_err(0, 0, ""); //TOFIX
		envlst_add_back(envars, new);
		free(new);
		i++;
	}
	set_ascii_indices(envars);
}

int count_args(char **cmd)
{
	int i;

	i = 1;
	// assuming cmd ends in NULL
	while (cmd[i] != NULL)
		i++;
	return (i);
}

void export(t_envar **envars, char **cmd)
{
	if (count_args(cmd) == 0)
		write_envars(*envars, true);
	else
		add_envars(envars, cmd);
}
