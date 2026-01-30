/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michi_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:33:40 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/30 16:24:23 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increment_shlvl(t_minishell *michi)
{
	t_envar	*shlvl;
	char	*str_value;
	int		value;

	shlvl = find_envar("SHLVL", michi->envars);
	if (shlvl->value)
	{
		value = ft_atoi(shlvl->value);
		value++;
		free(shlvl->value);
		str_value = ft_itoa(value);
		if (!str_value)
		{
			printf("itoa error: increment_shlvl\n");
			clean_env_list(michi);
			free(michi);
			exit(1);
		}
		shlvl->value = ft_strdup(str_value);
		free(str_value);
	}
}

static void	bzero_michi(t_minishell *michi)
{
	michi->envars = NULL;
	michi->cmds = NULL;
	michi->pfds = NULL;
	michi->pids = NULL;
	michi->input = NULL;
	michi->status = 0;
}

static void	init_err(t_minishell *michi, char *err)
{
	printf("shell-init error: %s\n", err);
	free(michi);
	exit(1);
}

t_minishell	*init_michishell(char **env)
{
	t_minishell	*michi;
	char		*pwd;

	print_cat();
	michi = malloc(sizeof(t_minishell));
	if (!michi)
		exit(1);
	bzero_michi(michi);
	pwd = ft_calloc(PATH_MAX, sizeof(char));
	if (!pwd)
		init_err(michi, "malloc: pwd");
	michi->pwd = getcwd(pwd, PATH_MAX);
	if (!michi->pwd)
	{
		free(pwd);
		init_err(michi, "couldn't get current working directory");
	}
	if (init_envars(michi, env, false))
	{
		free(pwd);
		init_err(michi, "init_envars");
	}
	increment_shlvl(michi);
	return (michi);
}
