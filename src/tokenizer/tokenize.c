/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/09 15:32:06 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tokenize(t_minishell *michi, int pipes)
{
	t_cmd	**head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (-1);
	while (pipes)
	{
		// Continue here tomorrow
		pipes--;
	}
}