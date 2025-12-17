/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/17 18:36:00 by gregueir         ###   ########.fr       */
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
		if (!is_breakpoint(line[i]) && !is_separator(line[i]))
			wcount++;
		if (line[i] == '>' || line[i] == '<')
			wcount -= 2;
		if (line[i] == '"')
			i += dquote_checker(line + i);
		else if (line[i] == '\'')
			i+= squote_checker(line + i);
		while (!is_breakpoint(line[i]) && !is_separator(line[i]))
			i++;
	}
	return (wcount);
}

static char	**split_input(char *line)
{
	int	i;
	int	words;

	i = 0;
	words = word_count(line);
	printf("Words found: %d\n", words);
	return (NULL);
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
