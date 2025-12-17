/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/17 20:30:04 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_breakpoint(char c)
{
	if (c == '|' || c == '\0' || c == '\n')
		return (true);
	return (false);
}

//Returns true if c is one of the designated word separators and false if not
static bool	is_separator(char c)
{
	if (c == ' ' || c == '\n')
		return (true);
	return (false);
}

int skip_redir(char *line)
{
	int i;

	i = 0;
	while (line[i] == '>' || line[i] == '<') // skip redirection chars
		i++;
	while (is_separator(line[i])) // skip separators (if any)
		i++;
	while (!is_breakpoint(line[i]) && !is_separator(line[i])) //after, skip word (non-separators)
		i++;
	return (i);
}

//Counts disctinct words (tokens) in the current Cmd, stops when finding a pipe
static int	word_count(char	*line)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (line && !is_breakpoint(line[i]))
	{
		while (line[i] && is_separator(line[i]))
			i++;
		if (line[i] == '>' || line[i] == '<')
			i += skip_redir(&line[i]);
		else if (!is_breakpoint(line[i]))
			wcount++;
		while (!is_breakpoint(line[i]) && !is_separator(line[i]))
		{
			if (line[i] == '"')
				i += dquote_checker(line + i);
			else if (line[i] == '\'')
				i+= squote_checker(line + i);
			i++;
		}
	}
	return (wcount);
}

static char *get_next_cmd_word(char **cmd, int j, char *line, int *i)
{
	int len;

	while (line && !is_breakpoint(line[*i]))
	{
		while (line[*i] && is_separator(line[*i]))
			*i++;
		if (line[*i] == '>' || line[*i] == '<')
			*i += skip_redir(&line[*i]);
		len = 0;
		while (!is_breakpoint(line[*i + len]) && !is_separator(line[*i + len]))
		{
			if (line[*i] == '"')
				len += dquote_checker(line + *i + len);
			else if (line[*i] == '\'')
				len += squote_checker(line + *i + len);
			else
				len++;
		}
		cmd[j] = ft_calloc(1, len /*+1*/ + 1); // len or len + 1 bc it starts at 0?
		// if there are quotes, len may be a bit larger but whatever
		if (!cmd[j])
			return NULL; // free all previous words!!!!!!!!!
		copy_word(cmd[j], &line[*i]);
		// copy len chars into cmd[j] while ignoring quotes TODO
		*i += len; // update current position in line
		return (cmd[j]);
	}
}

static char	**split_input(char *line)
{
	int	wcount;
	int j;
	int line_pos;
	char **cmd;

	wcount = word_count(line);
	printf("Words found: %d\n", wcount);
	char **cmd = ft_calloc(wcount + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	j = 0;
	line_pos = 0;
	while (cmd[j])
	{
		cmd[j] = get_next_cmd_word(cmd, j, line, &line_pos);
		j++;
	}
	copy_cmd_words(cmd, line);
}

int	tokenize(t_minishell *michi, int pipes)
{
	t_cmd	*head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (-1);
	head->cmd = split_input(michi->input);
	return (0);
}
