/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:16:28 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/26 16:00:32 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: Una función que cierre todos los FDs
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

void	exec(t_cmd *ptr, t_minishell *michi)
{
	char **env;

	if (is_builtin(ptr) == true)
	{
		builtin_execve(ptr, michi);
		michi_exit(michi, false, NULL);
	}
	env = env_list_to_arr(michi->envars);
	if (!env)
		michi_exit(michi, false,"exec_rest error: env");
	execve(ptr->path, ptr->cmd, env);
	fprintf(stderr, "Under execve\n");
	if (ptr->cmd[0])
		write(2, "Error: command not found\n", 26);
	fprintf(stderr, "status before modification: %i\n", michi->status);
	michi->status = 1;
	michi_exit(michi, false, NULL);
}

// receives cmd list, and env vars list
// sets up pipes
// starts children (needs to be modified in case builtin is passed)
// NOTE: only frees cmds, pipes, and pids but NOT env list so the user can keep using it!
void	wait_and_update(pid_t pid, t_minishell *michi)
{
	waitpid(pid, &michi->status, 0);
	if (WIFEXITED(michi->status))
		michi->status = WEXITSTATUS(michi->status);
	else if (WIFSIGNALED(michi->status))
		michi->status = WTERMSIG(michi->status) + 128;
}

void exec_single_cmd(t_minishell *michi)
{
	t_cmd *ptr;
	int pid;
	int old_stdout;

	old_stdout = dup(STDOUT_FILENO);
	ptr = michi->cmds;
	if (ptr->delim) // close other files?????
		get_heredoc(ptr, michi);
	dup2(michi->cmds->outfile, STDOUT_FILENO);
	if (is_builtin(ptr))
	{
		builtin_execve(ptr, michi);
		michi->status = 0;
		dup2(old_stdout, STDOUT_FILENO);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(ptr->infile, STDIN_FILENO);
		exec(michi->cmds, michi);
	}
	dup2(old_stdout, STDOUT_FILENO);
	wait_and_update(pid, michi);
}

void executor(t_minishell *michi)
{
	int		i;

	if (cmd_list_size(michi->cmds) == 1)
		return (exec_single_cmd(michi));
	michi->pfds = setup_pipes(&michi->cmds);
	michi->pids = malloc(cmd_list_size(michi->cmds) * sizeof(pid_t));
	if (!michi->pids)
		michi_exit(michi, false, "executor error: pids");
	start_children(michi);
	close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
	i = 0;
	while (i < cmd_list_size(michi->cmds))
		wait_and_update(michi->pids[i++], michi);
}

