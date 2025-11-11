/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/11 13:53:07 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Note: guille se encarga de expandir '$?'
void	echo(t_cmd *cmd)
{
	if (max_strncmp(cmd->cmd[1], "-n") == 0 && cmd->cmd[2])
		printf("%s\n", cmd->cmd[2]);
	else if (cmd->cmd[1])
		printf("%s", cmd->cmd[1]);
}
/*
Note: cd should change the working directory of a process!!!
But, it doesn't change the working directory of the current shell.
Because when the program is executed in the shell,
the shell follows fork on exec mechanism.
So, it doesn't affect the current shell.
*/

// maybe implement 'cd -'?
void	cd(t_cmd *cmd, t_envar **envars)
{
	char *buf;
	t_envar *oldpwd;
	t_envar *pwd;
	
	oldpwd = find_envar("OLDPWD", *envars);
	pwd = find_envar("PWD", *envars);
	if (!oldpwd || !pwd)
		exit(1); // handle error
	free(oldpwd->value);
	free(pwd->value);
	oldpwd->value = ft_calloc(1, PATH_MAX);
	pwd->value = ft_calloc(1, PATH_MAX);
	if (!oldpwd->value || !pwd->value)
		handle_err(errno, 2, ""); // fix
	getcwd(oldpwd->value, PATH_MAX);
	if (!oldpwd->value)
		exit(1); // handle error
	if (chdir(cmd->cmd[1]) != 0)
		handle_err(errno, 1, "filename"); // fix
	getcwd(pwd->value, PATH_MAX);
	if (!pwd->value)
		exit(1); // handle
	return ;
}

void	pwd(t_envar **envars)
{
	t_envar	*pwd;

	pwd = find_envar("PWD", *envars);
	if (!pwd)
	{
		perror("Couldn't find PWD\n");
		exit(1); // handle
	}
	printf("%s\n", pwd->value);
}

void	env(t_envar **envars)
{
	write_envars(*envars, true);
}

void	michi_exit(void)
{
	// Do later bc it may involve shutting down multiple processes
	return ;
}
