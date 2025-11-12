#include "minishell.h"

// receives cmd list, and env vars list
// sets up pipes
// starts children (needs to be modified in case builtin is passed)
int executor(t_minishell *michi)
{
	int		i;
	int		status;

    if (max_strncmp(michi->cmds->cmd[0], "exit") == 0 && cmd_list_size(michi->cmds) == 1)
        michi_exit(michi, true);
	michi->pfds = setup_pipes(&michi->cmds);
	michi->pids = malloc(cmd_list_size(michi->cmds) * sizeof(pid_t));
	if (!michi->pids)
		exit(1); //handle_err(&cmds, pfds);
	start_children(michi);
	close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
	i = 0;
	status = 0;
	while (i < cmd_list_size(michi->cmds) && status == 0)
		waitpid(michi->pids[i++], &status, 0);
	if (status != 0)
		printf("child exit unsuccessful\n");
	free(michi->pids);
	free_pipe_arr(michi->pfds);
	close_first_and_last(&michi->cmds);
	free_cmds(&michi->cmds); // maybe sub this for a michi_exit without the printf?  Make it your standard cleanup func?
	return (0);
}

