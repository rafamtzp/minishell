/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:11 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/03 17:54:18 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmdnode *node)
{
	char	*base;

	base = "echo/cd/pwd/export/unset/env/exit";
	if (ft_strnstr(base, node->cmd[0], ft_strlen(base)))
		return (true);
	return (false);
}

int	quote_finder(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input && input[i])
	{
		if (input[i] == '"')
			quotes++;
		i++;
	}
	if (!quotes)
		return (0);
	else if (quotes % 2 == 0)
		return (quotes / 2);
	return (-1);
}

int	parse_pipes(t_minishell *michi, char *input)
{
	int	i;
	int	pipes;
	int	quotes;

	pipes = 0;
	i = 0;
	quotes = quote_finder(input);
	if (quotes == -1)
	{
		ft_printf("I'm not dealing with this unclosed quites s*** mate\n");
		return (1);
	}
	// while (input && input[i])
	// {
	// 	if (input[i] == '|')
	// 	{
	// 		if (pipe_validator(input, i))
	// 			pipes++;
	// 	}
	// 	i++;
	// }
	// Split the input n times, where n is pipes + 1
	return(ft_printf("Found %d valid quotes\n", quotes));
}
