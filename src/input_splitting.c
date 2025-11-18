/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:11 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/18 17:01:44 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *node)
{
	if (max_strncmp("echo", node->cmd[0]) == 0 
	|| max_strncmp("cd", node->cmd[0]) == 0
	|| max_strncmp("pwd", node->cmd[0]) == 0
	|| max_strncmp("export", node->cmd[0]) == 0
	|| max_strncmp("unset", node->cmd[0]) == 0
	|| max_strncmp("env", node->cmd[0]) == 0
	|| max_strncmp("exit", node->cmd[0]) == 0)
		return (true);
	return (false);
}

/*int	quote_finder(char *input)
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
}*/

/*int	parse_pipes(t_minishell *michi, char *input)
{
	// int	i;
	// int	pipes;
	int	quotes;

	// pipes = 0;
	// i = 0;
	(void) michi; // comenté cosas para q el compilador se calle -Rafa
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
}*/

// int	input_parsing(t_minishell michi)
// {
// 	int		i;
// 	char	*input;
// 	char	**split;

// 	input = michi.input;
// 	i = 0;
// 	while (input && input[i])
// 	{
		
// 		i++;
// 	}
// }
