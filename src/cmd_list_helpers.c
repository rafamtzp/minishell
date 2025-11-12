/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:43:31 by rafamtz           #+#    #+#             */
/*   Updated: 2025/11/10 12:16:17 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*cmd_list_new(char *cmd, char *delim)
{
	t_cmd	*n;
	char	*delim_nl;

	n = malloc(sizeof(t_cmd));
	if (n == NULL)
	{
		printf("Unable to create node.\n");
		return (NULL);
	}
	delim_nl = NULL;
	if (delim)
		delim_nl = ft_strjoin(delim, "\n");
	if (delim && !delim_nl)
	{
		printf("Unable to create node.\n");
		return (NULL);
	}
	n->path = NULL;
	n->delim = delim_nl; // remember to free this!
	n->cmd = ft_split(cmd, ' ');
	n->is_append = false;
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
