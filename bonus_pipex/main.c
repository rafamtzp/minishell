/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:48:30 by rafamtz           #+#    #+#             */
/*   Updated: 2025/11/10 12:42:20 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	pid_t	*pids;
	int		i;
	t_cmd	*cmds;
	int		**pfds;
	int		status;

	pfds = NULL;
	cmds = NULL;
	parsing_storing_checking(argc, argv, &cmds); // different in minishell
	pfds = setup_pipes(&cmds);
	pids = malloc(cmd_list_size(cmds) * sizeof(pid_t));
	if (!pids)
		handle_err(&cmds, pfds);
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

// notes: if pfds = NULL, then there are no pipes.  i.e. only one command.
