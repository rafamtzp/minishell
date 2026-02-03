/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:16:28 by ramarti2          #+#    #+#             */
/*   Updated: 2026/02/03 20:11:45 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_single_cmd(t_minishell *michi, t_cmd *ptr)
{
	int		pid;
	int		old_stdout;

	old_stdout = dup(STDOUT_FILENO);
	dup2(michi->cmds->outfile, STDOUT_FILENO);
	if (is_builtin(ptr))
	{
		builtin_execve(ptr, michi);
		dup2(old_stdout, STDOUT_FILENO);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(ptr->infile, STDIN_FILENO);
		execve_wrapper(michi->cmds, michi);
	}
	wait_and_update(pid, michi);
	dup2(old_stdout, STDOUT_FILENO);
}

void	start_single_cmd(t_minishell *michi)
{
	t_cmd	*ptr;

	ptr = michi->cmds;
	if (ptr->delim)
		get_heredoc(ptr, michi);
	if (michi->status == 130)
		return ;
	exec_single_cmd(michi, ptr);
}

void	start_multiple_cmds(t_minishell *michi)
{
	t_cmd	*ptr;
	int		i;

	write_heredocs(michi);
	if (michi->status == 130)
		return ;
	ptr = michi->cmds;
	i = 0;
	while (ptr)
	{
		michi->pids[i] = fork();
		if (michi->pids[i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			dup2(ptr->outfile, STDOUT_FILENO);
			dup2(ptr->infile, STDIN_FILENO);
			close_pipe_ends(i, michi->pfds, cmd_list_size(michi->cmds));
			execve_wrapper(ptr, michi);
		}
		i++;
		ptr = ptr->next;
	}
}

void	executor(t_minishell *michi)
{
	int	i;

	if (cmd_list_size(michi->cmds) == 1)
		return (start_single_cmd(michi));
	michi->pfds = setup_pipes(&michi->cmds, michi);
	michi->pids = malloc(cmd_list_size(michi->cmds) * sizeof(pid_t));
	if (!michi->pids)
		michi_exit(michi, false, "executor error: pids");
	start_multiple_cmds(michi);
	close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
	i = 0;
	while (michi->status != 130 && i < cmd_list_size(michi->cmds))
		wait_and_update(michi->pids[i++], michi);
}
