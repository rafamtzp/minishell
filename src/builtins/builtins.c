/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/21 16:06:09 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Note: guille se encarga de expandir '$?'
void	echo(char **cmd)
{
	if (!cmd[1])
		printf("\n");
	else if (!cmd[2] && max_strncmp(cmd[1], "-n") == 0)
		printf("");
	else if (!cmd[2])
		printf("%s\n", cmd[1]);
	else if (max_strncmp(cmd[1], "-n") == 0)
		printf("%s", cmd[2]);
	// if (cmd[1] && max_strncmp(cmd[1], "-n") == 0 && cmd[2])
	// 	printf("%s", cmd[2]);
	// else if (cmd[1] && max_strncmp(cmd[1], "-n") == 0)
	// 	printf("");
	// else if (cmd[1])
	// 	printf("%s\n", cmd[1]);
	// else
	// 	printf("\n");
}
/*
Note: cd should change the working directory of a process!!!
But, it doesn't change the working directory of the current shell.
Because when the program is executed in the shell,
the shell follows fork on exec mechanism.
So, it doesn't affect the current shell.
*/
static int cd_calloc_new_values(t_envar *oldpwd, t_envar *pwd, char *prev_oldpwd, char *prev_pwd)
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

// maybe implement 'cd -'?
int	cd(char **cmd, t_minishell *michi)
{
	t_envar *oldpwd;
	char *prev_oldpwd;
	char *prev_pwd;
	t_envar *pwd;
	
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

void	pwd(t_minishell *michi)
{
	t_envar	*pwd;

	pwd = find_envar("PWD", michi->envars);
	if (!pwd)
		michi_exit(michi, false, "pwd");
	printf("%s\n", pwd->value);
}

void	env(t_envar *envars)
{
	write_envars(envars, false);
}

void	michi_exit(t_minishell *michi, bool print_msg, char *err_msg)
{
	int size;

	size = cmd_list_size(michi->cmds);
	close_pipe_ends(-1, michi->pfds, size);
	free_pipe_arr(michi->pfds);
	if (michi->pids)
		free(michi->pids);
	free_cmds(&michi->cmds);
	clean_env_list(michi);
	if (err_msg && max_strncmp("perror", err_msg) != 0)
		printf("Error: %s\n", err_msg);
	else if (err_msg && max_strncmp("perror", err_msg) == 0)
		perror("Error");
	if (print_msg == true)
		printf("exit\n");
	free(michi->input);
	//free(michi);
	exit(michi->status);
}
