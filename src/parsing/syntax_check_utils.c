/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:59 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/19 16:11:04 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(int errnum)
{
	if (errnum == 1)
		write(2, "Syntax error: Unclosed double quotes", 37);
	else if (errnum == 2)
		write(2, "Syntax error: Unclosed simple quotes", 37);
	else if (errnum == 3)
		write(2, "Syntax error: Unexpected token 'newline' or '|'", 48);
}

//Helper function, returns 1 if s has a \n or pipe after n spaces
static int	find_newline(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] == ' ')
		i++;
	if (s && (s[i] == '\n' || s[i] == '|'))
		return (0);
	else
		return (1);
}

//There's no way this works correctly, but testing it before everything is built is a pain, so test it when everything is built
//This function should check if there's a valid redirection, and if so, give it the green light
static int	syntax_check_redirection(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '>' && (s[i + 1] && s[i + 1] != '>'))
	{
		if (!find_newline(s + i))
			return (syntax_error(3), -1);
	}
	else if (s[i] == '>' && (s[i + 1] && s[i + 1] == '>'))
	{
		if (!find_newline(s + i))
			return (syntax_error(3), -1);
	}
	if (s[i] == '<' && (s[i + 1] && s[i + 1] != '<'))
	{
		if (!find_newline(s + i))
			return (syntax_error(3), -1);
	}
	else if (s[i] == '<' && (s[i + 1] && s[i + 1] == '<'))
	{
		if (!find_newline(s + i))
			return (syntax_error(3), -1);
	}
	return (i);
}

// Checks redirections on the given phrase, if they are fine it returns 0, if not, 1
int	syntax_check_redirect(char *s)
{
	int	i;
	int	checker;

	i = 0;
	checker = 0;
	while (s && s[i])
	{
		if (s[i] == '"')
			i += dquote_checker(s + i);
		else if (s[i] == '\'')
			i += squote_checker(s + i);
		else if (s[i] == '>' || s[i] == '<')
		{
			checker = syntax_check_redirection(s);
			if (checker == -1)
				return (1);
			i += checker;
		}
		i++;
	}
	return (0);
}
