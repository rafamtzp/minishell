/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:59:00 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/13 16:22:52 by gregueir         ###   ########.fr       */
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
		j = 0;
		if (s[i] == '\'')
		{
			squote = 1;
			while (s[i + j++] && squote == 1)
			{
				if (s[i + j] == '\'')
					return (j);
			}
		}
		i++;
	}
	return (0);
}

//Reads a line and checks if there are unclosed quotes or dquotes
static int	syntax_check_quotes(char *s)
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
				return (syntax_error(1), 1);
			i += distance;
		}
		else if (s[i] == '\'')
		{
			distance = squote_checker(s + i);
			if (!distance)
				return (syntax_error(2), 2);
			i += distance;
		}
		i++;
	}
	return (0);
}

static int	syntax_check_pipes(char *s)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (s && s[i])
	{
		if (s[i] == '"')
			i += (dquote_checker(s + i));
		else if (s[i] == '\'')
			i += (squote_checker(s + i));
		else if (s[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}

//Checks the syntax of s, if there's any error, prints it and returns -1. If there's no error, returns the number of usable pipes found
int	syntax_check(char *s)
{
	int	pipes;
	int	error;

	error = 0;
	error += syntax_check_quotes(s);
	error += syntax_check_redirect(s);
	pipes = syntax_check_pipes(s);
	if (error)
		return (-1);
	printf("Pipes found: %d\n", pipes);
	return (pipes);
}
