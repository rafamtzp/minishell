/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:56 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/23 14:44:10 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvarname(char *new_var)
{
	char	*varname;
	char	*ptr;

	varname = ft_strdup(new_var);
	if (!varname)
		return (NULL);
	ptr = varname;
	while (*ptr != '=')
		ptr++;
	*ptr = '\0';
	return (varname);
}

//TODO: Free those lists when done
t_envar	*envlst_new(char *new_var)
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

void	envlst_add_back(t_envar **envars, t_envar *new)
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

int	env_lstsize(t_envar *env)
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
