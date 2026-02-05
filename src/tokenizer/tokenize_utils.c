/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:38:59 by gregueir          #+#    #+#             */
/*   Updated: 2026/02/05 13:55:29 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_redir(char *line)
{
	int	i;

	i = 0;
	while (is_redirection(line[i]))
		i++;
	while (is_separator(line[i]))
		i++;
	while (!is_breakpoint(line[i]) && !is_separator(line[i])
		&& !is_redirection(line[i]))
	{
		if (is_quotes(line[i]))
		{
			if (line[i] == '"')
				i += dquote_checker(line + i) + 1;
			else
				i += squote_checker(line + i) + 1;
		}
		else
			i++;
	}
	return (i);
}

//Counts disctinct words (tokens) in the current Cmd, stops when finding a pipe
int	word_count(char	*line)
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
		while (!is_breakpoint(line[i]) && !is_separator(line[i])
			&& !is_redirection(line[i]))
		{
			if (line[i] == '"')
				i += dquote_checker(line + i);
			else if (line[i] == '\'')
				i += squote_checker(line + i);
			i++;
		}
	}
	return (wcount);
}

int	skip_var(char *word)
{
	int	i;

	i = 1;
	while (!is_breakpoint(word[i]) && !is_separator(word[i])
		&& !is_quotes(word[i]) && !is_nonalpha(word[i]))
		i++;
	return (i);
}

int	expansion_len(char *word, t_minishell *michi)
{
	int		wordlen;
	int		i;
	char	oldchar;
	t_envar	*ptr;

	i = 1;
	while (ft_isalnum(word[i]))
		i++;
	oldchar = word[i];
	word[i] = 0;
	wordlen = ft_strlen(word + 1);
	ptr = michi->envars;
	while (ptr)
	{
		if (ft_strncmp(word + 1, ptr->varname, wordlen) == 0)
		{
			word[i] = oldchar;
			if (ptr->value)
				return ((int)ft_strlen(ptr->value));
			return (0);
		}
		ptr = ptr->next;
	}
	word[i] = oldchar;
	return (0);
}

int	dquote_len(char *word, t_minishell *michi)
{
	int	len;
	int	i;

	i = 1;
	len = 0;
	while (word[i] && word[i] != '"')
	{
		if (word[i] == '$')
		{
			len += expansion_len(&word[i], michi);
			i += skip_var(&word[i]);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
