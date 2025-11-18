/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:07 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/18 15:12:14 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_alphabetically(t_envar *envar)
{
	int		i;
	int		size;
	t_envar	*head;

	head = envar;
	size = env_list_size(head);
	i = 0;
	while (i < size)
	{
		envar = head;
		while (envar && envar->ascii_index != i)
			envar = envar->next;
		if (envar && envar->value)
			printf("declare -x %s=\"%s\"\n", envar->varname, envar->value);
		else if (envar)
			printf("declare -x %s\n", envar->varname);
		i++;
	}
}

void	write_envars(t_envar *envar, bool order_alpha)
{
	if (order_alpha == true)
		print_alphabetically(envar);
	else
	{
		while (envar != NULL)
		{
			if (envar->value)
				printf("%s=%s\n", envar->varname, envar->value);
			envar = envar->next;
		}
	}
}

int	add_envars(t_minishell *michi, char **cmd, bool is_not_parsing)
{
	t_envar	*new;
	int		i;

	// assume params have format name=value
	i = is_not_parsing;
	while (cmd[i])
	{
		new = env_list_new(cmd[i]);
		if (!new)
		{
			//handle_err(errno, 0, ""); // TO IMPROVE
			return (1);
		}
		env_list_add_back(&michi->envars, new);
		i++;
	}
	set_ascii_indices(&michi->envars);
	return (0);
}

int	count_args(char **cmd)
{
	int	argcount;

	argcount = 0;
	// assuming cmd ends in NULL
	while (cmd[argcount] != NULL)
		argcount++;
	return (argcount);
}

int	export(t_minishell *michi, char **cmd) // unforked
{
	int status;

	status = 0;
	if (count_args(cmd) == 1)
		write_envars(michi->envars, true);
	else
		status = add_envars(michi, cmd, true);
	return (status);
}
