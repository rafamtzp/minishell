/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:59:00 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/20 15:47:52 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Returns 0 if dquotes aren't balanced and distance to next quote if they are
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
			while (s[i + j++] && dquote == 1)
			{
				if (s[i + j] == '"')
					return (j);
			}
		}
		i++;
	}
	return (0);
}

//Returns 0 if squotes aren't balanced and distance to next quote if they are
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
			while (s[i + j++] && squote == 1)
			{
				if (s[i + j] == '\'')
					return(j);
				j++;
			}
		}
		i++;
	}
	return (0);
}

int	syntax_check_quotes(char *s)
{
	int	i;
	int	distance;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '"')
		{
			distance = dquote_checker(s + i);
			if (!distance)
				return(perror("Sintax Error"), 1);
			i += distance;
		}
		else if (s[i] == '\'')
		{
			distance = squote_checker(s + i);
			if (!distance)
				return(perror("Sintax Error"), 2);
			i += distance;
		}
		i++;
	}
	return (0);
}

// int	main(int argv, char **args)
// {
// 	syntax_check_quotes(args[1]);
// 	return (0);
// }