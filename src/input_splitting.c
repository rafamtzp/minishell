/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:11 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/23 16:55:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(t_minishell *michi, char *input)
{
	int	i;
	int	pipes;

	pipes = 0;
	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|')
		{
			ft_printf("Pipe found");
			pipes++;
		}
		i++;
	}
	// Split the input n times, where n is pipes + 1
}
