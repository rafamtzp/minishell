/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/19 18:27:05 by ramarti2         ###   ########.fr       */
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

bool is_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

int skip_var(char *word)
{
	int i;

	i = 0;
	while (!is_breakpoint(word[i]) && !is_separator(word[i]) && !is_quotes(word[i]))
		i++;
	return (i);
}

int	expansion_len(char *word, t_minishell *michi)
{
	int wordlen;
	int i;
	char oldchar;
	char *var;
	t_envar *ptr;

	i = 1;
	while (!is_breakpoint(word[i]) && !is_separator(word[i]) && !is_quotes(word[i]))
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
			return (ft_strlen(ptr->value));
		}
		ptr = ptr->next;
	}
	word[i] = oldchar;
	return (0);
}

static int dquote_len(char *word, t_minishell *michi)
{
	int len;
	int i;

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

static int	get_wlen(char  *word, bool is_literal, t_minishell *michi)
{
	int wlen;
	int i;

	wlen = 0;
	i = -1;
	while (is_literal == true && !is_breakpoint(word[++i]) && !is_separator(word[i]))
		wlen++;
	while (is_literal == false && !is_breakpoint(word[++i]) && !is_separator(word[i]))
	{
		if (word[i] == '"')
		{
			wlen += dquote_len(&word[i], michi);
			i += dquote_checker(&word[i]);
		}
		else if (word[i] == '\'')
		{
			wlen += squote_checker(&word[i]) - 2;
			i += squote_checker(&word[i]);
		}
		else
			wlen++;
	}
	return (wlen);
}
//TODO:
char *extract_word(char *line, int wlen, t_minishell *michi, bool expand)
{
	char *word;
	int i;

	word = ft_calloc(1, wlen + 1);
	if (!word)
		return (NULL);
	i = 0;
	if (expand == true)
	{
		while (line[i] != '$' && i < wlen) // keep moving until you find a $
			word[i] = line[i++];
		// Note: you may find quotes before the $.  Make sure to not copy some of these!
		// Once you find the $ just look for the var, and copy its value into word (good luck).
		
	}
	ft_memcpy(word, line, wlen);
	return (word);
}

static char *get_next_word(char *line, bool reset, t_minishell *michi)
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
		if (!is_breakpoint(line[i]) && !is_separator(line[i]))
		{
			wlen = get_wlen(&line[i], false, michi);
			while (line[i] == '"' || line[i] == '\'')
				i++;
			word = extract_word(&line[i], wlen, /* TO DETERMINE */);
			i += get_wlen(&line[i], true, michi);
			break ;
		}
	}
	if(reset == true)
		i = 0;
	return (word);
}

static char	**split_input(char *line, t_minishell *michi)
{
	int	wcount;
	// int j;
	// int line_pos;
	char **cmd;
	int i;

	wcount = word_count(line);
	printf("Words found: %d\n", wcount);
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
		printf("%s\n", cmd[i]);
	exit(0);
	//j = 0;
	// line_pos = 0;
	// while (cmd[j])
	// {
	// 	cmd[j] = get_next_cmd_word(cmd, j, line, &line_pos);
	// 	j++;
	// }
	// copy_cmd_words(cmd, line);
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
