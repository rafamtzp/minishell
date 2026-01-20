/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/20 17:06:28 by gregueir         ###   ########.fr       */
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
// static int		test_count_words(char *input)
// {
// 	int i; int wc; int dq;
// 	i = dq = wc = 0;
// 	while (input[i])
// 	{
// 		while (input[i] && input[i] == ' ')
// 			i++;
// 		if (!input[i])
// 			break ;
// 		wc++;
// 		while (input[i] && ((input[i] != ' ' && dq % 2 == 0) || (dq % 2 == 1 && input[i] != '"')))
// 		{
// 			if (input[i] == '"')
// 				dq++;
// 			i++;
// 		}
// 		if (input[i] == '"')
// 		{
// 			dq++;
// 			i++;
// 		}
// 	}
// 	return wc;
// }
// char **test_input_splitting(char *input)
// {
// 	int wc = test_count_words(input);
// 	char **args = ft_calloc(sizeof(char *), 1 + wc + 1);
// 	if (!args)
// 	{
// 		perror("Malloc error");
// 		exit(1);
// 	}
// 	args[0] = ft_strdup("firstarg");
// 	args[wc + 1] = NULL;
// 	int i = 0;
// 	int j = 1;
// 	int dq = 0;
// 	while (input[i])
// 	{
// 		while (input[i] && input[i] == ' ')
// 			i++;
// 		if (input[i] == '"')
// 		{
// 			dq++;
// 			i++;
// 		}
// 		args[j++] = &input[i];
// 		while (input[i] && ((input[i] != ' ' && dq % 2 == 0) || (dq % 2 == 1 && input[i] != '"')))
// 			i++;
// 		if (input[i] == '"')
// 			dq++;
// 		if (input[i] == '"' || input[i] == ' ')
// 			input[i++] = 0;
// 	}
// 	return (args);
// }

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
