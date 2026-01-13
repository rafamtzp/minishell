/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_am_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:12:29 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/13 12:14:06 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Returns true if c is " or '
bool	is_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

//Returns true if c is | or \0 or Newline
bool	is_breakpoint(char c)
{
	if (c == '|' || c == '\0' || c == '\n')
		return (true);
	return (false);
}

//Returns true if c is Space or Newline
bool	is_separator(char c)
{
	if (c == ' ' || c == '\n')
		return (true);
	return (false);
}

//Returns true if c is < or >
bool	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}
