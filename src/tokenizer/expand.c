/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:14:50 by ramarti2          #+#    #+#             */
/*   Updated: 2026/02/05 14:08:35 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_tmp(char *tmp, char *word, t_minishell *michi)
{
	int		wlen;
	int		i;
	char	*value;
	int		free_doby;

	free_doby = 0;
	if (word[1] == '?')
	{
		free_doby = 1;
		value = ft_itoa(michi->status);
	}
	else
		value = extract_envar(michi, word);
	if (!value)
		return ;
	wlen = ft_strlen(value);
	i = 0;
	while (i < wlen)
	{
		tmp[i] = value[i];
		i++;
	}
	if (free_doby == 1)
		free(value);
}

void	fill_expanded_word(char *tmp, char *word, t_minishell *michi)
{
	int	qs;
	int	i;

	qs = 0;
	i = 0;
	while (word && *word)
	{
		qs = get_quote_status(*word, qs);
		if (*word == '$' && qs != -1)
		{
			fill_tmp(tmp + i, word, michi);
			i += expansion_len(word, michi);
			word += skip_var(word) - 1;
		}
		else if (!((qs == 0 && is_quotes(*word)) || (qs == 1 && *word == '"')
				|| (qs == -1 && *word == '\'')))
		{
			tmp[i] = *word;
			i++;
		}
		word++;
	}
}

char	*expander(char *word, t_minishell *michi)
{
	char	*tmp;
	int		explen;

	if (!word)
		return (NULL);
	explen = find_expanded_len(word, michi);
	tmp = ft_calloc(explen + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	fill_expanded_word(tmp, word, michi);
	return (tmp);
}

int	expand_cmds(t_cmd *cmds, t_minishell *michi)
{
	int		i;
	char	*unexpanded;
	t_cmd	*ptr;

	ptr = cmds;
	while (ptr)
	{
		i = 0;
		while (ptr->cmd[i])
		{
			unexpanded = ptr->cmd[i];
			ptr->cmd[i] = expander(ptr->cmd[i], michi);
			if (!ptr->cmd[i])
			{
				free(unexpanded);
				return (i);
			}
			free(unexpanded);
			i++;
		}
		ptr = ptr->next;
	}
	return (0);
}
