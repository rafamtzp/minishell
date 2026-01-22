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
	michi->status = 0;
}

// receives cmd list, and env vars list
// sets up pipes
// starts children (needs to be modified in case builtin is passed)
// NOTE: only frees cmds, pipes, and pids but NOT env list so the user can keep using it!
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
		dup2(old_stdout, STDOUT_FILENO);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(ptr->infile, STDIN_FILENO);
		exec(michi->cmds, michi);
	}
	dup2(old_stdout, STDOUT_FILENO);
	waitpid(pid, &michi->status, 0);
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
		waitpid(michi->pids[i++], &michi->status, 0);
}

