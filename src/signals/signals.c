/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 17:26:07 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/26 12:45:55 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// sigint handler para cuando estemos en un CAT o algo así (cerramos el CAT o lo que sea y ponemos el prompt)

//sigint handler para cuando estemos en terminal (ponemos newline y sacamos el prompt de nuevo)

void	sigint_handler(int	sigsent)
{
	char *tmp;

	(void)sigsent;
	tmp = readline("\n/^•⩊•^\\ michishell_$ ");
	free(tmp);
}