/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:15:10 by ramarti2          #+#    #+#             */
/*   Updated: 2026/02/03 20:13:06 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_next_exp_line(t_minishell *michi)
{
	char	*line;
	char	*exp_line;
	char	*line_nl;

	line = readline("🐾 ");
	if (!line)
		return (NULL);
	line_nl = ft_strjoin(line, "\n");
	free(line);
	exp_line = expander(line_nl, michi);
	free(line_nl);
	if (!exp_line)
	{
		write(2, "Error: Heredoc expansion\n", 26);
		return (NULL);
	}
	return (exp_line);
}

void	fill_heredoc(int write_end, t_cmd *ptr, t_minishell *michi)
{
	char	*exp_line;

	while (1)
	{
		exp_line = get_next_exp_line(michi);
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

static void	free_unused(t_minishell *michi)
{
	if (michi->pwd)
		free(michi->pwd);
	if (michi->input)
		free(michi->input);
	michi->pwd = NULL;
	michi->input = NULL;
}

void	get_heredoc(t_cmd *ptr, t_minishell *michi)
{
	int	hfd[2];
	int	pid;

	pipe(hfd);
	pid = fork();
	if (pid == 0)
	{
		free_unused(michi);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(hfd[READ_END]);
		fill_heredoc(hfd[WRITE_END], ptr, michi);
		close(hfd[WRITE_END]);
		close_pipe_ends(-1, michi->pfds, cmd_list_size(michi->cmds));
		michi_exit(michi, false, NULL);
	}
	wait_and_update(pid, michi);
	close(hfd[WRITE_END]);
	ptr->infile = hfd[READ_END];
}

void	write_heredocs(t_minishell *michi)
{
	t_cmd	*ptr;

	ptr = michi->cmds;
	while (ptr)
	{
		if (ptr->delim)
		{
			if (michi->status != 130)
				get_heredoc(ptr, michi);
		}
		ptr = ptr->next;
	}
}
