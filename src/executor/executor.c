#include "../minishell.h"

void	prep_for_next_cmd(t_minishell *michi)
{
	free(michi->pids);
	michi->pids = NULL;
	free_pipe_arr(michi->pfds);
	michi->pfds = NULL;
	//close_first_and_last(&michi->cmds);
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
void executor(t_minishell *michi)
{
	int		i;

	if (max_strncmp(michi->cmds->cmd[0], "exit") == 0 && cmd_list_size(michi->cmds) == 1)
		michi_exit(michi, true, NULL);
	michi->pfds = setup_pipes(&michi->cmds);
	michi->pids = malloc(cmd_list_size(michi->cmds) * sizeof(pid_t));
	if (!michi->pids)
		michi_exit(michi, false, "executor error: pids");
	start_children(michi);
	close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
	i = 0;
	while (i < cmd_list_size(michi->cmds))
	{
		waitpid(michi->pids[i++], &michi->status, 0);
		if (michi->status != 0)
			write(2, "Error: failed to execute command\n", 34);
	}
	prep_for_next_cmd(michi);
}

