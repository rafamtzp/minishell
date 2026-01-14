/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 11:48:48 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/14 16:12:55 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_filename(char *line)
{
	int i;
	int wlen;
	char *word;
	

	i = 0;
	while (is_redirection(line[i]) || is_separator(line[i]))
		i++;
	wlen = get_wlen(line + i);
	word = extract_word(line + i, wlen);
	word = clean_and_expand(word); //TODO
	return (word);
}

int	set_redir(char *line, t_cmd *ptr)
{
	//int DEBUGFD;
	char *filename;

	filename = get_filename(line);
	if (!filename)
		return (-1);
	if (line[0] == '>')
	{
		if (line[1] == '>')
			ptr->outfile = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
		else
			ptr->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		//DEBUGFD = ptr->outfile;
	}
	else
	{
		if (line[1] == '<')
			ptr->delim = ft_strjoin(filename, "\n");
		else
			ptr->infile = open(filename, O_RDONLY);
		//DEBUGFD = ptr->infile;
	}
	if (ptr->outfile == -1 || ptr->infile == -1)
		return (free(filename), -1);
	// //DEBUG
	// printf("filename: %s, fd: %i\n", filename, DEBUGFD);
	// free(filename);
	// int test=skip_redir(line);
	// printf("skip redir distance: %i\n", test);
	return (skip_redir(line));
}

int	skip_quotes(char *line)
{
	if (line[0] == '\'')
		return (squote_checker(line) + 1);
	return (dquote_checker(line) + 1);
}

void redirect_fds(t_cmd *ptr, char *line)
{
	int i;

	i = 0;
	while (ptr && line[i])
	{
		if (line[i] == '|')
		{
			ptr = ptr->next;
			i++;
		}
		else if (is_quotes(line[i]))
			i += skip_quotes(line + i);
		else if (is_redirection(line[i]))
			i += set_redir(line + i, ptr);
		else
			i++;
	}
}
