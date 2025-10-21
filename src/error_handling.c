/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:01 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/21 13:26:30 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_err(int errnum, int err, char *msg)
{
	(void)errnum;

	if (err == 1)
		printf("cd: %s: %s\n", strerror(errno), msg); // handle_err()
	else
		perror("Error");
	return ;
}
