/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:07 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/26 16:44:48 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int mod_envar(t_minishell *michi, char *arg)
{
	t_envar *var;
	char *varname;

	printf("Modifying envar\n");
	varname = getvarname(arg);
	var = find_envar(varname, michi->envars);
	if (var->value)
		free(var->value);
	if (ft_strchr(arg, '='))
	{
		var->value = ft_strdup(ft_strchr(arg, '=') + 1);
		if (!var->value)
			return (free(varname), write(2, "malloc err: export\n", 20));
	}
	else
		var->value = NULL;
	return (0);
}

int add_envar(t_minishell *michi, char *arg)
{
	t_envar *new;
	
	printf("Adding envar\n");
	new = env_list_new(arg);
	if (!new)
		return (write(2, "malloc err: export\n", 20));
	env_list_add_back(&michi->envars, new);
	return (0);
}

int	export(t_minishell *michi, char **cmd)
{
	char *varname;
	int status;
	int i;

	status = 0;
	if (count_args(cmd) == 1)
		write_envars(michi->envars, true);
	i = 1;
	while (count_args(cmd) > 1 && cmd[i])
	{
		varname = getvarname(cmd[i]);
		if (!find_envar(varname, michi->envars))
			status = add_envar(michi, cmd[i]);
		else if (ft_strchr(cmd[i], '='))
			status = mod_envar(michi, cmd[i]);
		free(varname);
		i++;
	}
	set_ascii_indices(&michi->envars);
	return (status);
}

