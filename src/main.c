/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/12 17:05:50 by ramarti2         ###   ########.fr       */
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
	michi->pfds = NULL;
	michi->pids = NULL;
	michi->input = NULL;
	add_envars(michi, env, false);
	return (michi);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*michi;
	// TEST VARIABLES:
	// char **test_input;
	// int	testc;

	print_cat();
	michi = init_michishell(env);
	clean_env_list(michi);
	while (1)
	{
		michi->input = readline("/^•⩊•^\\ ❀ michishell ❀ $ ");
		add_history(michi->input);

		parse_pipes(michi, michi->input);

		//------ TEST----------------
		// test_input = ft_split(michi->input, ' ');
		// testc = count_args(test_input) + 1; // +1 bc there is no './pipex'
		// parsing_storing_checking(testc, test_input, &michi->cmds);
		//----------------------------
		
		//Split the input
		
		// expand any variables in the input

		// create command nodes

		// execute nodes
		executor(michi);
	}
	return (0);
}

// 210,317k still reachables in readline