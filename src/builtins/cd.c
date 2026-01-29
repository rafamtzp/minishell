/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:41:25 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/29 14:24:41 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_calloc_new_values(t_envar *oldpwd, t_envar *pwd,
		char *prev_oldpwd, char *prev_pwd)
{
	oldpwd->value = ft_calloc(1, PATH_MAX);
	if (!oldpwd->value)
	{
		oldpwd->value = prev_oldpwd;
		return (1);
	}
	pwd->value = ft_calloc(1, PATH_MAX);
	if (!pwd->value)
	{
		free(oldpwd->value);
		pwd->value = prev_pwd;
		return (1);
	}
	return (0);
}

static int	chdir_wrapper(t_minishell *michi, char **cmd, char *prev_pwd)
{
	t_envar	*pwd;
	t_envar	*oldpwd;
	char	*appendage;

	oldpwd = find_envar("OLDPWD", michi->envars);
	pwd = find_envar("PWD", michi->envars);
	if (!getcwd(oldpwd->value, PATH_MAX))
		ft_strlcpy(oldpwd->value, prev_pwd, ft_strlen(prev_pwd) + 1);
	if (cmd[1] && chdir(cmd[1]) != 0)
	{
		michi->status = write(2, "couldn't chdir\n", 16);
		return (1);
	}
	else if (!cmd[1])
		return (chdir("/home"));
	if (!getcwd(pwd->value, PATH_MAX))
	{
		michi->status = write(2, "Error: couldn't getcwd\n", 24);
		appendage = ft_strjoin("/", cmd[1]);
		if (pwd->value)
			free(pwd->value);
		pwd->value = ft_strjoin(prev_pwd, appendage);
		free(appendage);
	}
	return (0);
}

int	cd(char **cmd, t_minishell *michi)
{
	t_envar	*oldpwd;
	char	*prev_oldpwd;
	char	*prev_pwd;
	t_envar	*pwd;

	oldpwd = find_envar("OLDPWD", michi->envars);
	pwd = find_envar("PWD", michi->envars);
	if (!oldpwd || !pwd)
		return (1);
	prev_oldpwd = oldpwd->value;
	prev_pwd = pwd->value;
	if (cd_calloc_new_values(oldpwd, pwd, prev_oldpwd, prev_pwd) == 1)
		return (1);
	if (chdir_wrapper(michi, cmd, prev_pwd) == 1)
	{
		free(pwd->value);
		free(oldpwd->value);
		pwd->value = prev_pwd;
		oldpwd->value = prev_oldpwd;
		return (1);
	}
	free(prev_pwd);
	free(prev_oldpwd);
	return (0);
}
