/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/20 17:15:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_wlen(char *word)
{
	int	i;

	i = 0;
	while (!is_breakpoint(word[i]) && !is_separator(word[i])
		&& !is_redirection(word[i]))
	{
		if (word[i] == '"')
			i += dquote_checker(word + i) + 1;
		else if (word[i] == '\'')
			i += squote_checker(word + i) + 1;
		else
			i++;
	}
	return (i);
}

char	*extract_word(char *line, int wlen)
{
	char	*word;

	word = ft_calloc(1, wlen + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, line, wlen);
	return (word);
}

static char	*get_next_word(char *line, bool reset)
{
	static int	i = 0;
	char		*word;
	int			wlen;

	word = NULL;
	while (!is_breakpoint(line[i]))
	{
		while (line[i] && is_separator(line[i]))
			i++;
		if (line[i] == '>' || line[i] == '<')
			i += skip_redir(&line[i]);
		if (!is_breakpoint(line[i]) && !is_separator(line[i])
			&& !is_redirection(line[i]))
		{
			wlen = get_wlen(&line[i]);
			word = extract_word(&line[i], wlen);
			i += wlen;
			break ;
		}
	}
	if (reset == true)
		i = 0;
	return (word);
}

static char	**split_input(char *line, int node_no)
{
	int		wcount;
	char	**cmd;
	int		i;

	while (node_no > 0)
	{
		if (line[0] == '|')
			node_no--;
		line++;
	}
	wcount = word_count(line);
	cmd = ft_calloc(wcount + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < wcount)
	{
		if (i == wcount - 1)
			cmd[i] = get_next_word(line, true);
		else
			cmd[i] = get_next_word(line, false);
		i++;
	}
	check_free_cmd(cmd, wcount);
	return (cmd);
}

int	tokenize(t_minishell *michi, int pipes)
{
	int		i;
	t_cmd	*node;

	i = 0;
	while (i < pipes + 1)
	{
		node = cmd_list_new();
		if (!node)
			return (free_cmds(&michi->cmds), -1);
		node->cmd = split_input(michi->input, i);
		cmd_list_add_back(&michi->cmds, node);
		i++;
	}
	redirect_fds(michi->cmds, michi->input, michi);
	expand_cmds(michi->cmds, michi);
	return (0);
}
