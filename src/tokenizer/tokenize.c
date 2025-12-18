/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/18 18:20:57 by ramarti2         ###   ########.fr       */
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

// static void copy_word(char *dest, char *src)
// {
// 	int i;
// 	int j;
// 	int dquotes;
// 	int squotes;

// 	dquotes = 0;
// 	squotes = 0;
// 	i = 0;
// 	j = 0;
// 	while (!is_breakpoint(src[i]) && (!is_separator(src[i]) || dquotes % 2 == 1 || squotes % 2 == 1))
// 	{
// 		//if dquote and squote %2 = 0, ONLY ignore dquotes and count
// 		//if squote and dquote%2=0, ONLY ignore squotes and count
// 		if (src[i] == '"' && dquotes % 2 == 0)
// 			dquotes++;
// 		else if (src[i] == '\'' && squotes % 2 == 0)
// 		if (src[i] != '"' && )
// 	}
// }

// static char *get_next_cmd_word(char **cmd, int j, char *line, int *i)
// {
// 	int len;

// 	while (line && !is_breakpoint(line[*i]))
// 	{
// 		while (line[*i] && is_separator(line[*i]))
// 			*i++;
// 		if (line[*i] == '>' || line[*i] == '<')
// 			*i += skip_redir(&line[*i]);
// 		len = 0;
// 		while (!is_breakpoint(line[*i + len]) && !is_separator(line[*i + len]))
// 		{
// 			if (line[*i] == '"')
// 				len += dquote_checker(line + *i + len);
// 			else if (line[*i] == '\'')
// 				len += squote_checker(line + *i + len);
// 			else
// 				len++;
// 		}
// 		cmd[j] = ft_calloc(1, len /*+1*/ + 1); // len or len + 1 bc it starts at 0?
// 		// if there are quotes, len may be a bit larger but whatever
// 		if (!cmd[j])
// 			return NULL; // free all previous words!!!!!!!!!
// 		copy_word(cmd[j], &line[*i]);
// 		// copy len chars into cmd[j] while ignoring quotes TODO
// 		*i += len; // update current position in line
// 		return (cmd[j]);
// 	}
// }

static int dquote_len(char *word, t_minishell *michi)
{
	int len;
	int i;

	i = 1;
	while (word[i] && word[i] != '"')
	{
		if (word[i] == '$')
		{
			len += expansion_len(word[i], michi);
			i += skip_var(word);
		}
		else
		{
			len++;
			i++;
		}
	}
}

static int	get_wlen(char  *word, bool is_literal, t_minishell *michi)
{
	int wlen;
	int i;

	wlen = 0;
	i = -1;
	while (is_literal == true && !is_breakpoint(word[++i]) && !is_separator(word[i]))
		wlen++;
	while (is_literal == false && !is_breakpoint(word[i]) && !is_separator(word[i]))
	{
		if (word[i] == '"')
		{
			wlen += dquote_len(&word[i], michi);
			i += dquote_checker(&word[i]);
		}
		else if (word[i] == "\'")
		{
			wlen += squote_checker(&word[i]) - 2;
			i += squote_checker(&word[i]);	
		}
		else
			wlen++;
		i++;
	}
	return (wlen);
}

static char *get_next_word(char *line, bool reset, t_minishell *michi)
{
	static int	i = 0;
	char		*word;
	int			wlen;
	// similar logic to wordcount
	while (line && !is_breakpoint(line[i]))
	{
		while (line[i] && is_separator(line[i]))
			i++;
		if (line[i] == '>' || line[i] == '<')
			i += skip_redir(&line[i]);
		if (!is_breakpoint(line[i]) && !is_separator(line[i]))
		{
			wlen = get_wlen(&line[i], false, michi);
			i += get_wlen(&line[i], true, michi);
			return (word);
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
	char **cmd = ft_calloc(wcount + 1, sizeof(char *));
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
