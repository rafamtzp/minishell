/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:59 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/13 12:43:22 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_error(int errnum)
{
	if (errnum == 1)
		write(2, "Syntax error: Unclosed double quotes\n", 38);
	else if (errnum == 2)
		write(2, "Syntax error: Unclosed simple quotes\n", 38);
	else if (errnum == 3)
		write(2, "Syntax error: Unexpected token\n", 32);
	else if (errnum == 4)
		write(2, "Syntax error: Too many redirections\n", 37);
}

//There's no way this works correctly, but testing it before everything is built is a pain, so test it when everything is built
//This function should check if there's a valid redirection, and if so, give it the green light
static int	syntax_check_redirection(char *s)
{
	int	i;

	i = 0;
	while (s[i] == s[0])
		i++;
	if (i > 2)
		return (syntax_error(4), -1);
	while (s[i] == ' ')
		i++;
	if (is_breakpoint(s[i]) || is_redirection(s[i]))
		return (syntax_error(3), -1);
	while (!is_separator(s[i]) && !is_breakpoint(s[i]) && !is_redirection(s[i]))
		i++;
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
			i += 1 + dquote_checker(s + i);
		else if (s[i] == '\'')
			i += 1 + squote_checker(s + i);
		else if (s[i] == '>' || s[i] == '<')
		{
			checker = syntax_check_redirection(s + i);
			if (checker == -1)
				return (1);
			i += checker;
		}
		else
			i++;
	}
	return (0);
}
