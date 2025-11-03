/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/03 17:03:10 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell *init_michishell(char **env)
{
	t_minishell	*michi;

	michi = malloc(sizeof(t_minishell));
	if (!michi)
		exit(1);
	michi->envars = NULL;
	michi->cmds = NULL;
	add_envars(&michi->envars, env, false);
	return (michi);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_minishell	*michishell;

	print_cat();
	michishell = init_michishell(env);
	clean_env_list(michishell);
	while (1)
	{
		input = readline("/^•⩊•^\\ ❀ michishell ❀ $ ");
		add_history(input);
		parse_pipes(michishell, input);
		//Split the input
		
		// expand any variables in the input

		// create command nodes

		// execute nodes
		
		//printf("You said: %s\n", input);
		free(input);
	}
	return (0);
}

// 210,317k still reachables in readline