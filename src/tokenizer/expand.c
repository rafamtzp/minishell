/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:14:50 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/19 16:07:30 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_tmp(char *tmp, char *word, t_minishell *michi)
{
	int		wlen;
	int		i;
	char	*value;

	value = extract_envar(michi, word);
	wlen = ft_strlen(value);
	i = 0;
	while (i < wlen)
	{
		tmp[i] = value[i];
		i++;
	}
}

void	fill_expanded_word(char *tmp, char *word, t_minishell *michi)
{
	int qs;
	int i;
	
	qs = 0;
	i = 0;
	while (*word)
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

	explen = find_expanded_len(word, michi);
	tmp = ft_calloc(explen + 1, sizeof(char));
	if (!tmp)
		return (NULL); //Controlar errores
	fill_expanded_word(tmp, word, michi);
	return (tmp);
}

void	expand_cmds(t_cmd *cmds, t_minishell *michi)
{
	int i;
	char *unexpanded;

	i = 0;
	while (cmds)
	{
		while (cmds->cmd[i])
		{
			unexpanded = cmds->cmd[i];
			cmds->cmd[i] = expander(cmds->cmd[i], michi);
			free(unexpanded);
			i++;
		}
		cmds = cmds->next;
	}
}
