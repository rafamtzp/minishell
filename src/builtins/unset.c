/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:19:23 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/27 13:05:00 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	del_env(t_envar **envars, t_envar **ptr1, t_envar **ptr2)
{
	t_envar	*ptr3;

	free((*ptr1)->varname);
	free((*ptr1)->value);
	if (*ptr1 == *envars)
	{
		*envars = (*envars)->next;
		*ptr1 = (*ptr1)->next;
		free(*ptr2);
		*ptr2 = *ptr1;
	}
	else if (*ptr1)
	{
		ptr3 = *ptr1;
		*ptr1 = (*ptr1)->next;
		(*ptr2)->next = *ptr1;
		free(ptr3);
	}
}

int	unset(t_envar **envars, char **cmd)
{
	int		i;
	t_envar	*ptr1;
	t_envar	*ptr2;

	i = 1;
	ptr1 = *envars;
	ptr2 = *envars;
	while (ptr1 && *envars && cmd[i] != NULL)
	{
		while (ptr1 && max_strncmp(ptr1->varname, cmd[i]) != 0)
		{
			ptr1 = ptr1->next;
			if (ptr1 && max_strncmp(ptr1->varname, cmd[i]) != 0)
				ptr2 = ptr2->next;
		}
		if (ptr1)
			del_env(envars, &ptr1, &ptr2);
		else
		{
			write(2, "Variable does not exist\n", 25);
			return (1);
		}
		i++;
	}
	return (0);
}
