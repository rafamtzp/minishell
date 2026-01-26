/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:41:25 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/26 16:54:31 by ramarti2         ###   ########.fr       */
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
		pwd->value = prev_pwd;
		return (1);
	}
	free(prev_oldpwd);
	free(prev_pwd);
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
	if (!getcwd(oldpwd->value, PATH_MAX))
		return (1);
	if (chdir(cmd[1]) != 0)
		return (1);
	getcwd(pwd->value, PATH_MAX);
	if (!pwd->value)
		return (1);
	return (0);
}
