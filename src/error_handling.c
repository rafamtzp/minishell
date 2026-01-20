/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:01 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/20 13:56:30 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_err(t_minishell *michi, char *msg)
{
	(void)michi;
	if (msg)
		printf("Error: %s\n", msg);
	else
		perror("Error");
}

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
	else if (errnum == 5)
		write(2, "Syntax error: Empty pipe\n", 26);
}
