/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/21 19:02:04 by ramarti2         ###   ########.fr       */
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
	michi->status = 0;
	add_envars(michi, env, false);
	return (michi);
}
static int		test_count_words(char *input)
{
	int i; int wc; int dq;
	i = dq = wc = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		wc++;
		while (input[i] && ((input[i] != ' ' && dq % 2 == 0) || (dq % 2 == 1 && input[i] != '"')))
		{
			if (input[i] == '"')
				dq++;
			i++;
		}
		if (input[i] == '"')
		{
			dq++;
			i++;
		}
	}
	return wc;
}
char **test_input_splitting(char *input)
{
	int wc = test_count_words(input);
	char **args = ft_calloc(sizeof(char *), 1 + wc + 1);
	if (!args)
	{
		perror("Malloc error");
		exit(1);
	}
	args[0] = ft_strdup("firstarg");
	args[wc + 1] = NULL;
	int i = 0;
	int j = 1;
	int dq = 0;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '"')
		{
			dq++;
			i++;
		}
		args[j++] = &input[i];
		while (input[i] && ((input[i] != ' ' && dq % 2 == 0) || (dq % 2 == 1 && input[i] != '"')))
			i++;
		if (input[i] == '"')
			dq++;
		if (input[i] == '"' || input[i] == ' ')
			input[i++] = 0;
	}
	return (args);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	*michi;

	//print_cat();
	michi = init_michishell(env);
	//clean_env_list(michi);
	while (1)
	{
		//michi->input = readline("/^•⩊•^\\ ❀ michishell ❀ $ ");
		michi->input = readline("/^•⩊•^\\ michishell_$ ");
		add_history(michi->input);
		//parse_pipes(michi, michi->input); //uncomment all for testing
		
		//------ TEST ----------------
		int wc = test_count_words(michi->input);
		char **args = test_input_splitting(michi->input);
		parsing_storing_checking(wc + 1, args, &michi->cmds);
		free(args[0]);
		free(args);
		//----------------------------
		//Split the input
		
		// expand any variables in the input
		
		// create command nodes
		
		// execute nodes
		executor(michi);
		prep_for_next_cmd(michi);
		
	}
	return (0);
}

// 210,317k still reachables in readline
