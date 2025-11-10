/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:46:01 by rafamtz           #+#    #+#             */
/*   Updated: 2025/11/10 12:16:13 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	start_heredoc(t_cmd *ptr)
{
	int		hfd[2];
	char	*line;

	pipe(hfd);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, ptr->delim, max_strlen(line, ptr->delim)) == 0)
		{
			close(hfd[WRITE_END]);
			break ;
		}
		write(hfd[WRITE_END], line, ft_strlen(line));
		ptr->infile = hfd[READ_END];
	}
}

void	start_children(t_cmd *cmds, pid_t *pids, int **pfds, char **env)
{
	t_cmd	*ptr;
	int		i;

	ptr = cmds;
	i = 0;
	while (ptr)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			dup2(ptr->outfile, STDOUT_FILENO);
			if (ptr->delim)
				start_heredoc(ptr);
			dup2(ptr->infile, STDIN_FILENO);
			close_pipe_ends(i, pfds, cmd_list_size(cmds));
			execve(ptr->path, ptr->cmd, env);
			exit(1);
		}
		i++;
		ptr = ptr->next;
	}
}
