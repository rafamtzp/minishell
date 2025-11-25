/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:59:00 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/25 13:04:34 by gregueir         ###   ########.fr       */
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

//Reads a line and checks if there are unclosed quotes or dquotes
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
				return(perror("Syntax Error"), 1);
			i += distance;
		}
		else if (s[i] == '\'')
		{
			distance = squote_checker(s + i);
			if (!distance)
				return(perror("Syntax Error"), 2);
			i += distance;
		}
		i++;
	}
	return (0);
}

int	syntax_check_pipes(char *s)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while(s && s[i])
	{
		if (s[i] == '"')
			i += i + (dquote_checker(s + i));
		else if (s[i] == '\'')
			i += i + (squote_checker(s + i));
		else if (s[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

int	syntax_check(char *s)
{
	int	i;
	int	pipes;

	i = 0;
	syntax_check_quotes(s);
	pipes = syntax_check_pipes(s);
	//printf("Pipes found: %d\n", pipes);
	return (pipes);
}

// int	main(int argv, char **args)
// {
// 	syntax_check(args[1]);
// 	return (0);
// }