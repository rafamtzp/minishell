/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:59:00 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/19 15:25:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dquote_checker(char *s)
{
	int	i;
	int	j;
	int	dquote;

	i = 0;
	dquote = 0;
	while (s && s[i])
	{
		j = 0;
		if (s[i] == '"')
		{
			dquote = 1;
			while (s[i + j] && dquote == 1)
			{
				if (s[i + j] == '"' && (s[i + j + 1] == ' ' || !s[i + j + 1]))
					dquote = 0;
				j++;
			}
			i = i + j;
		}
		i++;
	}
	return (dquote);
}

int	main(int argc, char **args)
{
	int	unclosed_quotes = dquote_checker(args[1]);
	printf("Unclosed quotes: %d\n", unclosed_quotes);
}