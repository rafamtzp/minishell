/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/15 13:38:58 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	char *input;
	(void) argc;
	(void) argv;
	(void) env;
	
	// store all env vars into struct

	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		// split the input

		// expand any variables in the input

		// create command nodes

		// execute nodes
		
		printf("You said: %s\n", input);
		free(input);
	}
    return (0);
}

// 200k still reachables in readline