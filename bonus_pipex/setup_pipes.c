/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:16:42 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/10 13:00:29 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**create_pipes(t_cmd *cmds, int **pfds)
{
	int	i;

	if (cmd_list_size(cmds) > 0)
		pfds = malloc((cmd_list_size(cmds) - 1 + 1) * sizeof(int *));
	if (!pfds)
		handle_err(&cmds, pfds);
	i = 0;
	while (i < cmd_list_size(cmds) - 1)
	{
		pfds[i] = malloc(2 * sizeof(int));
		if (!pfds[i])
		{
			close_pipe_ends(-1, pfds, cmd_list_size(cmds)); // will this work?
			handle_err(&cmds, pfds);
		}
		if (pipe(pfds[i]) == -1)
			handle_err(&cmds, pfds);
		i++;
	}
	pfds[i] = NULL;
	return (pfds);
}
/*
what does this do?

1. should've already received the file descriptors of each node (guille)
bonus pipex case:
if there's a delim (here_doc case), open a temporary pipe during execution
if it's the last node,
	open argv[last] and save to outfile (check that argv[last] isn't malicious)
minishell case:
much more complicated to assign fds to nodes but that's not my job

2. This just creates pipes array and takes the nodes with assigned fds and asks,
Assuming	infile = stdin and outfile = stdout by default:
- if infile == stdin && not first node:
-    infile = reading end of prev
- if outfile == stdout && not last node:
-    outfile = writing end of next
- else: already opened and assigned properly
*/
int	**setup_pipes(t_cmd **cmds)
{
	t_cmd	*ptr;
	int		**pfds;
	int		i;

    if (cmd_list_size(*cmds) == 1)
        return (NULL);
    pfds = NULL;
    pfds = create_pipes(*cmds, pfds);
    ptr = *cmds;
    i = 0;
    // link commands with pipes by assigning cmds to their pfds.
    while (ptr->next && pfds[i])
    {
        if (ptr->infile == STDIN_FILENO && ptr != *cmds)
            ptr->infile = pfds[i - 1][READ_END];
        if (ptr->outfile == STDOUT_FILENO && ptr->next != NULL)
            ptr->outfile = pfds[i][WRITE_END];
        ptr = ptr->next;
        i++;
    }
    if (ptr->next == NULL)
        ptr->infile = pfds[i - 1][READ_END];
    return (pfds);
}
