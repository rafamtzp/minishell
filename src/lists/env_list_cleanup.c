/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 14:28:51 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/19 12:04:27 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_list(t_minishell *michi)
{
	t_envar	*current;
	t_envar *buff;

	current = michi->envars;
	while (current)
	{
		buff = current->next;
		free(current);
		current = buff;
	}
	free(michi);
}

void	clean_env_list(t_minishell *michi)
{
	t_envar	*current;

	if (!michi->envars)
		return ;
	current = michi->envars;
	while(current)
	{
		if (current->varname)
		{
			free(current->varname);
			current->varname = NULL;
		}
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
		current = current->next;
	}
	clean_list(michi);
}
