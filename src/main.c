/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/20 17:41:02 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_minishell	*init_michishell(char **env, int argc, char **argv)
{
	t_minishell	*michi;

	(void)argc;
	(void)argv;
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
	tokenize(michi, pipes);
	find_paths(michi->cmds, michi);
	executor(michi);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		*michi;
	int				pipes;

	michi = init_michishell(env, argc, argv);
	while (1)
	{
		michi->input = readline("/^•⩊•^\\ michishell_$ ");
		if (!michi->input)
		{
			prep_for_next_cmd(michi);
			printf("exit\n");
			return (0);
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
	clean_env_list(michi);
	return (0);
}

// 210,317k still reachables in readline
