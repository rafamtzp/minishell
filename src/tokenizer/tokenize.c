/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 11:39:57 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/12 16:14:11 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Counts disctinct words (tokens) in the current Cmd, stops when finding a pipe
static int	word_count(char	*line)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (line && line[i] && line[i] != '|')
	{
		if (line[i] == '"')
			i += dquote_checker(line + i);
		else if (line[i] == '\'')
			i+= squote_checker(line + i);
		if (line[i] == ' ' || line[i] == '<'
			|| line[i] == '>' || line[i] == '|')
		{
			if (i != 0 && (line[i - 1] != ' ' || line[i - 1] != '<'
				|| line[i - 1] != '>'))
					wcount++;
		}
		i++;
	}
	if (line[i - 1] != ' ' || line[i - 1] != '<' || line[i - 1] != '>')
		wcount++;
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
