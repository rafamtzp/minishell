/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:46:38 by rafamtz           #+#    #+#             */
/*   Updated: 2025/11/10 12:41:39 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe_ends(int i, int **pfds, int size)
{
	int	j;

	if (pfds == NULL)
		return ;
	if (i > 0)
		close(pfds[i - 1][WRITE_END]);
	if (i < size - 1 && i > -1) // added size-1 to fix bug
		close(pfds[i][READ_END]);
	j = 0;
	while (j < size - 1)
	{
		if (j != i && j != i - 1)
		{
			close(pfds[j][READ_END]);
			close(pfds[j][WRITE_END]);
		}
		j++;
	}
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (!cmds || !(*cmds))
		return ;
	current = *cmds;
	while (current)
	{
		next = current->next;
		i = 0;
		if (current->delim)
			free(current->delim);
		if (current->path)
			free(current->path);
		while (current->cmd && current->cmd[i])
			free(current->cmd[i++]);
		if (current->cmd)
			free(current->cmd);
		free(current);
		current = next;
	}
	*cmds = NULL;
}

void	free_pipe_arr(int **pfds)
{
	int	i;

	if (!pfds)
		return ;
	i = 0;
	while (pfds[i])
		free(pfds[i++]);
	free(pfds);
}

void	close_first_and_last(t_cmd **cmds)
{
	t_cmd	*ptr;

	if (!cmds || !(*cmds))
		return ;
	ptr = *cmds;
	if (ptr && ptr->infile != STDIN_FILENO && ptr->infile != -1)
		close(ptr->infile);
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->outfile != STDOUT_FILENO && ptr->outfile != -1)
		close(ptr->outfile);
}

void	handle_err(t_cmd **cmds, int **pfds)
{
	perror("Error");
	free_pipe_arr(pfds);
	close_first_and_last(cmds);
	free_cmds(cmds);
	exit(1);
}
