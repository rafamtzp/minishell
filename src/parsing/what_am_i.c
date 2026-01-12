/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_am_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:12:29 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/12 15:17:10 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

bool	is_breakpoint(char c)
{
	if (c == '|' || c == '\0' || c == '\n')
		return (true);
	return (false);
}

bool	is_separator(char c)
{
	if (c == ' ' || c == '\n')
		return (true);
	return (false);
}

bool	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}
