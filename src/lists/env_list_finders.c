/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_finders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:18:13 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/26 14:18:44 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envar	*find_envar(char *varname, t_envar *ptr)
{
	while (ptr && max_strncmp(ptr->varname, varname) != 0)
		ptr = ptr->next;
	return (ptr);
}

char	*getvarname(char *new_var)
{
	char	*varname;
	char	*ptr;

	varname = ft_strdup(new_var);
	if (!varname)
		return (NULL);
	ptr = varname;
	while (*ptr && *ptr != '=')
		ptr++;
	*ptr = '\0';
	return (varname);
}
