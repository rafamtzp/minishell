/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:56 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/26 14:19:51 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_envars(t_minishell *michi, char **cmd, bool is_not_parsing)
{
	t_envar	*new;
	int		i;

	i = is_not_parsing;
	while (cmd[i])
	{
		new = env_list_new(cmd[i]);
		if (!new)
			return (1);
		env_list_add_back(&michi->envars, new);
		i++;
	}
	set_ascii_indices(&michi->envars);
	return (0);
}

t_envar	*env_list_new(char *new_var)
{
	t_envar	*new;

	new = malloc(sizeof(t_envar));
	if (!new)
		return (NULL);
	new->varname = getvarname(new_var);
	if (ft_strchr(new_var, '=') != 0)
	{
		new->value = ft_strdup(ft_strchr(new_var, '=') + 1);
		if (!new->value)
		{
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->ascii_index = 0;
	new->next = NULL;
	return (new);
}

void	env_list_add_back(t_envar **envars, t_envar *new)
{
	t_envar *ptr;

	if (new == 0)
		return ;
	ptr = *envars;
	if (*envars == 0)
	{
		*envars = new;
		return ;
	}
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
}

int	env_list_size(t_envar *env)
{
	int		count;

	if (!env)
		return (0);
	count = 0;
	while (env)
	{
		count++;
		env = env -> next;
	}
	return (count);
}
