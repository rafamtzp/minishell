/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_mem_mgmt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:26:23 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/13 15:50:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_free_cmd(char	**cmd, int wcount)
{
	int	i;
	int	nulls;

	i = 0;
	nulls = 0;
	while (i < wcount)
	{
		if (cmd[i] == NULL)
			nulls++;
		i++;
	}
	i = 0;
	while (nulls && i < wcount)
	{
		if (cmd[i])
			free(cmd[i]);
		i++;
	}
	if (nulls && cmd)
	{
		free(cmd);
		cmd = NULL;
	}
}
