/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:26:07 by gregueir          #+#    #+#             */
/*   Updated: 2026/02/03 15:40:18 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	g_sigstatus = 0;

void	set_sigstatus(int stat)
{
	g_sigstatus = stat;
}

void	sigint_handler(int sigsent)
{
	(void)sigsent;
	if (g_sigstatus == 2)
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		ft_putendl_fd("", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
