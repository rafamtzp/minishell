/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/30 16:21:04 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_and_execute(t_minishell *michi, int pipes)
{
	michi->status = tokenize(michi, pipes);
	if (michi->status != 0)
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
		set_sigstatus(2);
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
		set_sigstatus(0);
		if (michi->status == 131)
			printf("Quit (core dumped)\n");
		prep_for_next_cmd(michi);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*michi;

	if (argc != 1 || argv[1])
	{
		write(2, "Too many arguments\n", 20);
		return (1);
	}
	if (!env || !env[0])
	{
		write(2, "Feed me env pls /ᐠ｡‸｡ᐟ\\\n", 35);
		return (1);
	}
	michi = init_michishell(env);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	main_loop(michi);
	michi_exit(michi, false, NULL);
	return (0);
}

// 208,213k still reachables in readline
