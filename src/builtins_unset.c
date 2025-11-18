/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:23 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/18 16:49:11 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env(t_envar **ptr1, t_envar **ptr2, bool ishead)
{
	t_envar *ptr3;
	
	free((*ptr1)->varname);
	free((*ptr1)->value);
	if (ishead == true)
	{
		*ptr1 = (*ptr1)->next;
		free(*ptr2);
		*ptr2 = *ptr1;
	}
	else
	{
		ptr3 = *ptr1;
		*ptr1 = (*ptr1)->next;
		(*ptr2)->next = *ptr1;
		free(ptr3);
	}
}

int	unset(t_envar **envars, char **cmd) // unforked
{
	int i;
	t_envar *ptr1;
	t_envar *ptr2;

	i = 1;
	ptr1 = *envars;
	ptr2 = *envars;
	while (ptr1 && *envars && cmd[i] != NULL)
	{
		while (ptr1 && max_strncmp(ptr1->varname, cmd[i]) != 0)
		{
			ptr1 = ptr1->next;
			if (max_strncmp(ptr1->varname, cmd[i]) != 0)
				ptr2 = ptr2->next;
		}
		if (ptr1 == *envars)
		{
			*envars = (*envars)->next;
			del_env(&ptr1, &ptr2, true);
		}
		else
			del_env(&ptr1, &ptr2, false);
		i++;
	}
	return (0);
}
