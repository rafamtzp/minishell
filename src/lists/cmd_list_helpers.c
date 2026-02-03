/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:43:31 by rafamtz           #+#    #+#             */
/*   Updated: 2026/02/03 18:13:55 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*cmd_list_new(void)
{
	t_cmd	*n;

	n = malloc(sizeof(t_cmd));
	if (n == NULL)
		return (NULL);
	n->path = NULL;
	n->delim = NULL;
	n->cmd = NULL;
	n->infile = STDIN_FILENO;
	n->outfile = STDOUT_FILENO;
	n->next = NULL;
	return (n);
}

void	cmd_list_add_back(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*ptr;

	if (new == NULL)
		return ;
	ptr = *cmds;
	if (*cmds == NULL)
	{
		*cmds = new;
		return ;
	}
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
}

int	cmd_list_size(t_cmd *cmd)
{
	int	size;

	if (cmd == NULL)
		return (0);
	size = 1;
	while (cmd->next != NULL)
	{
		cmd = cmd->next;
		size++;
	}
	return (size);
}

static void	free_cmd_content(t_cmd *current)
{
	int			i;
	struct stat	buf;

	i = 0;
	if (current->delim)
		free(current->delim);
	if (current->path)
		free(current->path);
	while (current->cmd && current->cmd[i])
	{
		free(current->cmd[i]);
		i++;
	}
	if (current->cmd)
		free(current->cmd);
	if (current->infile != STDIN_FILENO && fstat(current->infile, &buf) == 0)
		close(current->infile);
	if (current->outfile != STDOUT_FILENO && fstat(current->outfile, &buf) == 0)
		close(current->outfile);
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;

	if (!cmds || !(*cmds))
		return ;
	current = *cmds;
	while (current)
	{
		next = current->next;
		free_cmd_content(current);
		free(current);
		current = next;
	}
	*cmds = NULL;
}
