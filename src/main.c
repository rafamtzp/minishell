/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:38:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/17 16:16:52 by ramarti2         ###   ########.fr       */
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
	args[0] = "firstarg";
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
		michi->input = readline("/^•⩊•^\\ michishell $ ");
		add_history(michi->input);
		//parse_pipes(michi, michi->input); //uncomment all for testing
		
		//------ TEST ----------------
		int wc = test_count_words(michi->input);
		//printf("wc: %i\n", wc + 1);
		char **args = test_input_splitting(michi->input);
		// for (int i = 0; args[i]; i++)
		// 	printf("%s\n", args[i]);
		parsing_storing_checking(wc + 1, args, &michi->cmds);
		// parsing doesnt work for multiple args.  Only single commands
		for (t_cmd *ptr = michi->cmds; ptr; ptr = ptr->next)
			printf("cmd: %s, arg: %s\n", ptr->cmd[0], ptr->cmd[1]);
		//----------------------------
		
		//Split the input
		
		// expand any variables in the input

		// create command nodes

		// execute nodes
		executor(michi);
		//--------TEST------------------
		printf("Cannot be looped rn\n");
		//exit(0);
		//-----------------------------
	}
	return (0);
}

// 210,317k still reachables in readline

