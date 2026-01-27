/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:16:36 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/27 13:09:13 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	close_pipe_ends(int i, int **pfds, int size)
{
	int	j;

	if (pfds == NULL)
		return ;
	if (i > 0)
		close(pfds[i - 1][WRITE_END]);
	if (i < size - 1 && i > -1)
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

int	**create_pipes(t_minishell *michi, t_cmd *cmds, int **pfds)
{
	int	i;

	if (cmd_list_size(cmds) > 0)
		pfds = malloc((cmd_list_size(cmds) - 1 + 1) * sizeof(int *));
	if (!pfds)
		michi_exit(michi, false, "malloc error: create_pipes");
	i = 0;
	while (i < cmd_list_size(cmds) - 1)
	{
		pfds[i] = malloc(2 * sizeof(int));
		if (!pfds[i])
			michi_exit(michi, false, "malloc error: create_pipes");
		if (pipe(pfds[i]) == -1)
			michi_exit(michi, false, "syscall pipe() error: create_pipes");
		i++;
	}
	pfds[i] = NULL;
	return (pfds);
}

int	**setup_pipes(t_cmd **cmds, t_minishell *michi)
{
	t_cmd	*ptr;
	int		**pfds;
	int		i;

	if (cmd_list_size(*cmds) == 1)
		return (NULL);
	pfds = NULL;
	pfds = create_pipes(michi, *cmds, pfds);
	ptr = *cmds;
	i = 0;
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
