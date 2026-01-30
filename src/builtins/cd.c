/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:41:25 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/30 16:26:31 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_envar	*create_pwd(t_minishell *michi, char *pwd_type)
{
	t_envar	*pwdvar;

	pwdvar = find_envar(pwd_type, michi->envars);
	if (!pwdvar)
	{
		if (add_envar(michi, pwd_type) != 0)
			michi_exit(michi, false, "cd: add_envar");
		pwdvar = find_envar(pwd_type, michi->envars);
	}
	return (pwdvar);
}

static char	*create_and_update_pwds(char **cmd, t_minishell *michi,
		char *prev_pwd)
{
	t_envar	*pwdvar;
	t_envar	*oldpwdvar;
	char	*appendage;

	pwdvar = create_pwd(michi, "PWD");
	oldpwdvar = create_pwd(michi, "OLDPWD");
	if (oldpwdvar->value)
		free(oldpwdvar->value);
	oldpwdvar->value = prev_pwd;
	if (pwdvar->value)
		free(pwdvar->value);
	pwdvar->value = getcwd(NULL, 0);
	if (!pwdvar->value)
	{
		write(2, "cd: current working directory not found\n", 41);
		appendage = ft_strjoin("/", cmd[1]);
		if (!appendage)
			michi_exit(michi, false, "cd2: strjoin: malloc");
		pwdvar->value = ft_strjoin(prev_pwd, appendage);
		free(appendage);
		if (!pwdvar->value)
			michi_exit(michi, false, "cd2: strjoin: malloc");
	}
	return (pwdvar->value);
}

int	cd(char **cmd, t_minishell *michi)
{
	char	*prev_pwd;
	char	*pwd;

	prev_pwd = ft_strdup(michi->pwd);
	if (!prev_pwd)
		michi_exit(michi, false, "cd: malloc");
	if (!cmd[1] || max_strncmp(cmd[1], "~") == 0)
	{
		chdir("/home");
		create_and_update_pwds(cmd, michi, prev_pwd);
		return (0);
	}
	if (chdir(cmd[1]) != 0)
		return (write(2, "cd: no such file or directory\n", 31));
	pwd = create_and_update_pwds(cmd, michi, prev_pwd);
	if (michi->pwd)
		free(michi->pwd);
	michi->pwd = ft_strdup(pwd);
	if (!michi->pwd)
		michi_exit(michi, false, "cd: ft_strdup");
	return (0);
}
