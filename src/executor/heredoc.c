/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:15:10 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/26 13:09:44 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_next_exp_line(int fd, t_minishell *michi)
{
	char *line;
	char *exp_line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	exp_line = expander(line, michi);
	free(line);
	if (!exp_line)
	{
		write(2, "Error: Heredoc expansion\n", 26);
		return (NULL);
	}
	return (exp_line);
}

void fill_heredoc(int write_end, t_cmd *ptr, t_minishell *michi)
{
	char *exp_line;

	while (1)
	{
		write(1, "🐾 ", 6);
		exp_line = get_next_exp_line(STDIN_FILENO, michi);
		if (!exp_line)
			return ;
		if (max_strncmp(exp_line, ptr->delim) == 0)
		{
			free(exp_line);
			return ;
		}
		write(write_end, exp_line, ft_strlen(exp_line));
		free(exp_line);
	}
}

void	get_heredoc(t_cmd *ptr, t_minishell *michi)
{
	int		hfd[2];
	int pid;

	pipe(hfd);
	pid = fork();
	if (pid == 0)
	{
		close(hfd[READ_END]);
		fill_heredoc(hfd[WRITE_END], ptr, michi);
		close(hfd[WRITE_END]);
		close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
		michi_exit(michi, false, NULL);
	}
	waitpid(pid, &michi->status, 0);
	close(hfd[WRITE_END]);
	ptr->infile = hfd[READ_END];
}


void	write_heredocs(t_minishell *michi)
{
	t_cmd *ptr;

	ptr = michi->cmds;
	while (ptr)
	{
		if (ptr->delim)
		{
			if (ptr->infile != STDIN_FILENO)
				close(ptr->infile);
			get_heredoc(ptr, michi);
		}
		ptr = ptr->next;
	}
}