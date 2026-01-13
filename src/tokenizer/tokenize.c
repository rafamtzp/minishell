/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/13 12:43:54 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_wlen(char *word, t_minishell *michi, char init)
{
	int	wlen;
	int	i;

	wlen = 0;
	i = -1;
	if (init == '"')
		wlen = 1 + dquote_checker(word);
	else if (init == '\'')
		wlen = 1 + squote_checker(word);
	while (init != '"' && init != '\''
		&& !is_breakpoint(word[++i]) && !is_separator(word[i])
		&& !is_redirection(word[i]))
		wlen++;
	return (wlen);
}

static char	*extract_word(char *line, int wlen, t_minishell *michi)
{
	char	*word;
	int		i;

	word = ft_calloc(1, wlen + 1);
	if (!word)
		return (NULL);
	i = -1;
	while (++i < wlen)
		word[i] = line[i];
	ft_memcpy(word, line, wlen);
	return (word);
}

static char	*get_next_word(char *line, bool reset, t_minishell *michi)
{
	static int	i = 0;
	char		*word;
	int			wlen;

	while (line && !is_breakpoint(line[i]))
	{
		while (line[i] && is_separator(line[i]))
			i++;
		if (line[i] == '>' || line[i] == '<')
			i += skip_redir(&line[i]);
		if (!is_breakpoint(line[i]) && !is_separator(line[i])
			&& !is_redirection(line[i]))
		{
			wlen = get_wlen(&line[i], michi, line[i]);
			//printf("Wlen = %d\n", wlen);
			word = extract_word(&line[i], wlen, michi);
			i += wlen;
			break ;
		}
	}
	if (reset == true)
		i = 0;
	return (word);
}

static char	**split_input(char *line, t_minishell *michi)
{
	int		wcount;
	char	**cmd;
	int		i;

	wcount = word_count(line);
	//printf("Words found: %d\n", wcount);
	cmd = ft_calloc(wcount + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < wcount)
	{
		if (i == wcount - 1)
			cmd[i] = get_next_word(line, true, michi);
		else
			cmd[i] = get_next_word(line, false, michi);
		i++;
	}
	for (int i = 0; cmd[i]; i++)
		printf("CMD %d = %s\n", i, cmd[i]);
	return (cmd);
}

int	tokenize(t_minishell *michi, int pipes)
{
	t_cmd	*head;

	head = malloc(sizeof(t_cmd));
	if (!head)
		return (-1);
	head->cmd = split_input(michi->input, michi);
	return (0);
}
