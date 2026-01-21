/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/21 16:06:53 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	*init_michishell(char **env)
{
	t_minishell	*michi;

	//print_cat();
	michi = malloc(sizeof(t_minishell));
	if (!michi)
		exit(1);
	michi->envars = NULL;
	michi->cmds = NULL;
	michi->pfds = NULL;
	michi->pids = NULL;
	michi->input = NULL;
	michi->status = 0;
	if (add_envars(michi, env, false))
	{
		free(michi);
		exit(1);
	}
	return (michi);
}

static void	setup_and_execute(t_minishell *michi, int pipes)
{
	int	err;

	err = 0;
	err = tokenize(michi, pipes);
	if (err)
		return ;
	find_paths(michi->cmds, michi);
	executor(michi);
}

static void	main_loop(t_minishell *michi)
{
	int	pipes;

	while (1)
	{
		michi->input = readline("/^•⩊•^\\ michishell_$ ");
		if (!michi->input)
		{
			prep_for_next_cmd(michi);
			printf("exit\n");
			return ;
		}
		add_history(michi->input);
		pipes = syntax_check(michi->input);
		if (pipes == -1)
		{
			prep_for_next_cmd(michi);
			continue ;
		}
		setup_and_execute(michi, pipes);
		prep_for_next_cmd(michi);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		*michi;

	if (argc != 1 || argv[1])
	{
		write(2, "Too many arguments\n", 20);
		return (1);
	}
	michi = init_michishell(env);
	main_loop(michi);
	clean_env_list(michi);
	return (0);
}

// 210,317k still reachables in readline
