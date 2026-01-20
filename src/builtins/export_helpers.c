/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:33 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/20 15:40:32 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	max_strncmp(char *s1, char *s2)
{
	int max_len;
	
	if (ft_strlen(s1) > ft_strlen(s2))
		max_len = ft_strlen(s1);
	else
		max_len = ft_strlen(s2);
	return (ft_strncmp(s1, s2, max_len));
}


void	set_ascii_indices(t_envar **s)
{
	t_envar	*ptr;
	t_envar *ptr2;

	ptr = *s;
	if (ptr == NULL)
		return ;
	set_empty_indices(s);
	while (ptr != NULL)
	{
		ptr2 = *s;
		while (ptr2 != NULL)
		{
			if (max_strncmp(ptr->varname, ptr2->varname) > 0)
				ptr->ascii_index++;
			ptr2 = ptr2->next;
		}
		ptr = ptr->next;
	}
	return ;
}
