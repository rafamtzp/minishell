/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:48:48 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/28 12:28:27 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_filename(char *line, t_minishell *michi)
{
	int		i;
	int		wlen;
	char	*word;
	char	*tmp;

	i = 0;
	while (is_redirection(line[i]) || is_separator(line[i]))
		i++;
	wlen = get_wlen(line + i);
	tmp = extract_word(line + i, wlen);
	word = expander(tmp, michi);
	if (tmp)
		free(tmp);
	return (word);
}

static void	assign_fd(t_cmd *ptr, char *filename, char *line)
{
	struct stat	buf;

	if (line[0] == '>')
	{
		if (ptr->outfile != STDOUT_FILENO && fstat(ptr->outfile, &buf) == 0)
			close(ptr->outfile);
		if (line[1] == '>')
			ptr->outfile = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
		else
			ptr->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		if (ptr->infile != STDIN_FILENO && fstat(ptr->infile, &buf) == 0)
			close(ptr->infile);
		if (line[1] == '<')
			ptr->delim = ft_strjoin(filename, "\n");
		else
			ptr->infile = open(filename, O_RDONLY);
	}
}

static int	set_redir(char *line, t_cmd *ptr, t_minishell *michi)
{
	char	*filename;

	filename = get_filename(line, michi);
	if (!filename)
		return (-1);
	assign_fd(ptr, filename, line);
	if (ptr->outfile == -1 || ptr->infile == -1)
		return (free(filename), -1);
	if (filename)
		free(filename);
	return (skip_redir(line));
}

int	skip_quotes(char *line)
{
	if (line[0] == '\'')
		return (squote_checker(line) + 1);
	return (dquote_checker(line) + 1);
}

int	redirect_fds(t_cmd *ptr, char *line, t_minishell *michi)
{
	int	increment;
	int	i;

	i = 0;
	while (ptr && line[i])
	{
		if (line[i] == '|')
		{
			ptr = ptr->next;
			i++;
		}
		else if (is_quotes(line[i]))
			increment = skip_quotes(line + i);
		else if (is_redirection(line[i]))
			increment = set_redir(line + i, ptr, michi);
		else
			increment = 1;
		if (increment == -1)
		{
			write(2, "Error: Could not open file\n", 28);
			return (1);
		}
		i += increment;
	}
	return (0);
}
