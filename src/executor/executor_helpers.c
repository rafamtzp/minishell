/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:16:22 by ramarti2          #+#    #+#             */
/*   Updated: 2026/02/05 16:15:06 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_list_to_arr(t_envar *env)
{
	char	**env_arr;
	char	*tmp;
	int		i;

	env_arr = ft_calloc(env_list_size(env) + 1, sizeof(char *));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->varname, "=");
		if (env->value)
			env_arr[i] = ft_strjoin(tmp, env->value);
		else
			env_arr[i] = ft_strdup(tmp);
		free(tmp);
		if (!env_arr[i])
		{
			free_str_arr(env_arr);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	return (env_arr);
}

void	wait_and_update(pid_t pid, t_minishell *michi)
{
	waitpid(pid, &michi->status, 0);
	if (WIFEXITED(michi->status))
		michi->status = WEXITSTATUS(michi->status);
	else if (WIFSIGNALED(michi->status))
		michi->status = WTERMSIG(michi->status) + 128;
}

void	builtin_execve(t_cmd *ptr, t_minishell *michi)
{
	if (ptr->infile != STDIN_FILENO)
		close(ptr->infile);
	if (max_strncmp(ptr->cmd[0], "echo") == 0)
		echo(ptr->cmd);
	else if (max_strncmp(ptr->cmd[0], "pwd") == 0)
		pwd(michi);
	else if (max_strncmp(ptr->cmd[0], "env") == 0)
		env(michi->envars);
	else if (max_strncmp(ptr->cmd[0], "cd") == 0)
		michi->status = cd(ptr->cmd, michi);
	else if (max_strncmp(ptr->cmd[0], "export") == 0)
		michi->status = export(michi, ptr->cmd);
	else if (max_strncmp(ptr->cmd[0], "unset") == 0)
		michi->status = unset(&michi->envars, ptr->cmd);
	else if (max_strncmp(ptr->cmd[0], "exit") == 0
		&& cmd_list_size(michi->cmds) == 1)
		michi_exit(michi, true, NULL);
	if (cmd_list_size(michi->cmds) > 1)
		michi_exit(michi, false, NULL);
}

void	prep_for_next_cmd(t_minishell *michi)
{
	if (michi->pids)
	{
		free(michi->pids);
		michi->pids = NULL;
	}
	if (michi->pfds)
	{
		free_pipe_arr(michi->pfds);
		michi->pfds = NULL;
	}
	free_cmds(&michi->cmds);
	michi->cmds = NULL;
	free(michi->input);
	michi->input = NULL;
}

void	execve_wrapper(t_cmd *ptr, t_minishell *michi)
{
	char	**env;

	if (is_builtin(ptr) == true)
	{
		builtin_execve(ptr, michi);
		michi_exit(michi, false, NULL);
	}
	env = env_list_to_arr(michi->envars);
	if (!env)
		michi_exit(michi, false, "exec_rest error: env");
	if (ptr->path)
		execve(ptr->path, ptr->cmd, env);
	if (ptr->cmd[0])
		write(2, "Error: unable to execute\n", 26);
	free_str_arr(env);
	michi->status = 1;
	michi_exit(michi, false, NULL);
}
