/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:23 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/20 13:19:29 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_env(t_envar **ptr1, t_envar **ptr2, t_envar **ptr3, bool ishead)
{
	free((*ptr1)->varname);
	free((*ptr1)->value);
	if (ishead == true)
	{
		if (*ptr2 != *ptr1)
			(*ptr2) = (*ptr2)->next;
		*ptr1 = (*ptr1)->next;
		free(ptr2);
		*ptr2 = *ptr1;
	}
	else
	{
		*ptr3 = *ptr1;
		*ptr1 = (*ptr1)->next;
		free(*ptr3);
		(*ptr2)->next = *ptr1;
	}
}

void	unset(t_envar **envars, char **cmd)
{
	int i;
	t_envar *ptr1;
	t_envar *ptr2;
	t_envar *ptr3;

	i = 1;
	ptr1 = *envars;
	ptr2 = *envars;
	while (cmd[i] != NULL)
	{
		while (ptr1->varname != cmd[i])
		{
			ptr1 = ptr1->next;
			if (ptr1->varname != cmd[i])
				ptr2 = ptr2->next;
		}
		if (ptr1 == *envars)
		{
			*envars = (*envars)->next;
			del_env(&ptr1, &ptr2, &ptr3, true);
		}
		else
			del_env(&ptr1, &ptr2, &ptr3, false);
	}
}
