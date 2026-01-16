/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:14:50 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/16 14:08:27 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_quote_status(char c, int stat)
{
	if (c == '"' && stat == 0)
			stat = 1;
	else if (c == '"' && stat == 1)
			stat = 0;
	if (c == '\'' && stat == 0)
			stat = -1;
	else if (c == '\'' && stat == -1)
			stat = 0;
	return (stat);
}

char	*extract_envar(t_minishell *michi, char *word)
{
	char	*str;
	char	*envname;
	t_envar	*envar;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = "";
	envname = ft_calloc(ft_strlen(word), sizeof(char));
	if (!envname)
		return (NULL); //Cleanup memory here
	while (word[++i] && ft_isalnum(word[i]))
	{
		envname[j] = word[i];
		j++;
	}
	//printf("Envname is: %s\n", envname);
	envar = find_envar(envname, michi->envars);
	if (envar)
		str = envar->value;
	free(envname);
	return (str);
}

int		find_expanded_len(char *word, t_minishell *michi)
{
	int qs;
	int len;

	qs = 0;
	len = 0;
	while (*word)
	{
		qs = get_quote_status(*word, qs);
		if (*word == '$' && qs != -1)
		{
			len += expansion_len(word, michi);
			word += skip_var(word) - 1;
		}
		else if (!((qs == 0 && is_quotes(*word)) || (qs == 1 && *word == '"')
				|| (qs == -1 && *word == '\'')))
			len++;
		word++;
	}
	return (len);
}

void	fill_tmp(char *tmp, char *word, t_minishell *michi)
{
	int		wlen;
	int		i;
	char	*value;

	value = extract_envar(michi, word);
	wlen = ft_strlen(value);
	//printf("Value is: %s\n", value);
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
			//printf("Tmp has: %s\n", tmp);
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
	//printf("Tmp has: %s\n", tmp);
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
