/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/12 14:49:01 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Note: guille se encarga de expandir '$?'
void	echo(char **cmd)
{
	if (max_strncmp(cmd[1], "-n") == 0 && cmd[2])
		printf("%s\n", cmd[2]);
	else if (cmd[1])
		printf("%s", cmd[1]);
}
/*
Note: cd should change the working directory of a process!!!
But, it doesn't change the working directory of the current shell.
Because when the program is executed in the shell,
the shell follows fork on exec mechanism.
So, it doesn't affect the current shell.
*/

// maybe implement 'cd -'?
void	cd(char **cmd, t_minishell *michi)
{
	char *buf;
	t_envar *oldpwd;
	t_envar *pwd;
	
	oldpwd = find_envar("OLDPWD", michi->envars);
	pwd = find_envar("PWD", michi->envars);
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
	if (chdir(cmd[1]) != 0)
		handle_err(errno, 1, "filename"); // fix
	getcwd(pwd->value, PATH_MAX);
	if (!pwd->value)
		exit(1); // handle
	return ;
}

void	pwd(t_minishell *michi)
{
	t_envar	*pwd;

	pwd = find_envar("PWD", michi->envars);
	if (!pwd)
	{
		perror("Couldn't find PWD\n");
		exit(1); // handle
	}
	printf("%s\n", pwd->value);
}

void	env(t_envar *envars)
{
	write_envars(envars, true);
}

void	michi_exit(t_minishell *michi, bool print_msg)
{
	close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
	free_pipe_arr(michi->pfds);
	if (michi->pids)
		free(michi->pids);
	free_cmds(&michi->cmds);
	clean_env_list(michi);
	if (print_msg == true)
		printf("exit\n");
	exit(0);
}
