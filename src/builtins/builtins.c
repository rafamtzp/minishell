/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/19 15:44:02 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Note: guille se encarga de expandir '$?'
void	echo(char **cmd)
{
	if (cmd[1] && max_strncmp(cmd[1], "-n") == 0 && cmd[2])
		printf("%s", cmd[2]);
	else if (cmd[1])
		printf("%s\n", cmd[1]);
}
/*
Note: cd should change the working directory of a process!!!
But, it doesn't change the working directory of the current shell.
Because when the program is executed in the shell,
the shell follows fork on exec mechanism.
So, it doesn't affect the current shell.
*/

// maybe implement 'cd -'?
int	cd(char **cmd, t_minishell *michi)
{
	t_envar *oldpwd;
	char *old_oldpwd;
	char *old_pwd;
	t_envar *pwd;
	
	oldpwd = find_envar("OLDPWD", michi->envars);
	pwd = find_envar("PWD", michi->envars);
	if (!oldpwd || !pwd)
		return (1);
	old_oldpwd = oldpwd->value;
	old_pwd = pwd->value;
	oldpwd->value = ft_calloc(1, PATH_MAX);
	if (!oldpwd->value)
		return (oldpwd->value = old_oldpwd, 1);
	pwd->value = ft_calloc(1, PATH_MAX);
	if (!pwd->value)
		return (pwd->value = old_pwd, 1);
	free(old_oldpwd);
	free(old_pwd);
	getcwd(oldpwd->value, PATH_MAX);
	if (!oldpwd->value)
		return (1);
	if (chdir(cmd[1]) != 0)
		handle_err(michi, NULL);
	getcwd(pwd->value, PATH_MAX);
	if (!pwd->value)
		return (1);
	return (0);
}

void	pwd(t_minishell *michi)
{
	t_envar	*pwd;

	pwd = find_envar("PWD", michi->envars);
	if (!pwd)
		handle_err(michi, "pwd");
	printf("%s\n", pwd->value);
}

void	env(t_envar *envars)
{
	write_envars(envars, false);
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
	//free(michi->input);
	exit(michi->status);
}
