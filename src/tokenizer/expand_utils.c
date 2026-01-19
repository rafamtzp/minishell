/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:21:06 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/19 16:07:57 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_quote_status(char c, int stat)
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
