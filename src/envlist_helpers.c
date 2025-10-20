/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:56 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/20 13:20:01 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getvarname(char *new_var)
{
	char	*varname;
	char	*ptr;

	varname = ft_strdup(new_var);
	ptr = varname;
	while (ptr != '=')
		ptr++;
	*ptr = '\0';
	return (varname);
}

t_envar	*envlst_new(t_envar **envars, char *new_var)
{
	t_envar	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->varname = getvarname(new_var);
	new->value = ft_strdup(ft_strchr(new_var, '=') + 1); // free these!
	new->next = NULL;
	return (new);
}

void	envlst_add_back(t_envar **envars, t_envar *new)
{
	t_envar *ptr;

	if (ptr == 0 || new == 0)
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
