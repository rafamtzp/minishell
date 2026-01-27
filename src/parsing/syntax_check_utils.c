/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:59 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/27 11:58:10 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//This function should check if there's a valid redirection
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

// Checks redirections on the given phrase, if they are fine it returns 0
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

bool	pipe_check_empty(char *s)
{
	int	i;

	i = 1;
	while (s && is_separator(s[i]))
		i++;
	if (!s[i] || s[i] == '|' || s[i] == '\n')
		return (true);
	else
		return (false);
}
