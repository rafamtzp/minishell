/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:59:00 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/20 13:18:46 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Returns 1 if dquotes aren't balanced and 0 if they are
int	dquote_checker(char *s)
{
	int	i;
	int	j;
	int	dquote;

	i = 0;
	dquote = 0;
	while (s && s[i])
	{
		j = 1;
		if (s[i] == '"')
		{
			dquote = 1;
			while (s[i + j] && dquote == 1)
			{
				if (s[i + j] == '"')
					dquote = 0;
				j++;
			}
			i = i + j;
		}
		i++;
	}
	return (dquote);
}

//Returns 1 if squotes aren't balanced and 0 if the are
int	squote_checker(char *s)
{
	int	i;
	int	j;
	int	squote;

	i = 0;
	squote = 0;
	while (s && s[i])
	{
		j = 1;
		if (s[i] == '\'')
		{
			squote = 1;
			while (s[i + j] && squote == 1)
			{
				if (s[i + j] == '\'')
					squote = 0;
				j++;
			}
			i = i + j;
		}
		i++;
	}
	return (squote);
}

int	syntax_check(char *s)
{
	int	i;
	if (dquote_checker(s) || squote_checker(s))
		return (perror("Sintax error"), 1);
	printf("Success\n");
	return (0);
}

// int	main(int argv, char **args)
// {
// 	syntax_check(args[1]);
// 	return (0);
// }