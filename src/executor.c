#include "minishell.h"

// receives cmd list, and env vars list
// sets up pipes
// starts children (needs to be modified in case builtin is passed)
int executor(t_cmd **cmds, t_envar **envars)
{
    pid_t	*pids;
	int		i;
	int		**pfds;
	int		status;

    if (max_strncmp((*cmds)->cmd[0], "exit") == 0)
        michi_exit(); // make sure to free everything!!!!!!
	pfds = NULL;
	pfds = setup_pipes(&cmds);
	pids = malloc(cmd_list_size(cmds) * sizeof(pid_t));
	if (!pids)
		exit(1); //handle_err(&cmds, pfds);
	start_children(cmds, pids, pfds, env);
	close_pipe_ends(-1, pfds, cmd_list_size(cmds));
	i = 0;
	status = 0;
	while (i < cmd_list_size(cmds) && status == 0)
		waitpid(pids[i++], &status, 0);
	if (status != 0)
		printf("child exit unsuccessful\n");
	free(pids);
	free_pipe_arr(pfds);
	close_first_and_last(&cmds);
	free_cmds(&cmds);
	return (0);
}

