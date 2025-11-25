/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:59 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/25 13:23:05 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	syntax_check_redirection(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '>' && (s[i + 1] && s[i + 1] != '>'))
	{
		// Redirect output
	}
	else 
	{
		//Redirect output in append mode
	}
	if (s[i] == '<' && (s[i + 1] && s[i + 1] != '<'))
	{
		//redirect input
	}
	else
	{
		//next word is delimiter and you read from terminal into the heredoc
	}
}

int	syntax_check_redirect(char *s)
{
	int	i;

	i = 0;
	while(s && s[i])
	{
		if (s[i] == '"')
			i += i + (dquote_checker(s + i));
		else if (s[i] == '\'')
			i += i + (squote_checker(s + i));
		else if (s[i] == '>' || s[i] == '<')
		{
			i += check_redirection(s);
		}
		i++;
	}
	return (0);
}
