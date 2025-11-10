/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:33 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/10 13:27:41 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_empty_indices(t_envar **s)
{
	t_envar	*ptr;

	if (*s == NULL || s == NULL)
		return ;
	ptr = *s;
	while (ptr != NULL)
	{
		ptr->ascii_index = 0;
		ptr = ptr->next;
	}
	return ;
}

int	max_strlen(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	return (ft_strlen(s2));
}


void	set_ascii_indices(t_envar **s)
{
	t_envar	*ptr;
	t_envar *ptr2;
	int		i;

	ptr = *s;
	if (ptr == NULL)
		return ;
	set_empty_indices(s);
	i = 0;
	while (ptr != NULL)
	{
		ptr2 = *s;
		while (ptr2 != NULL)
		{
			if (ft_strncmp(ptr->varname, ptr2->varname, max_strlen(ptr->varname, ptr2->varname)) > 0)
				ptr->ascii_index++;
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return ;
}
