/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:01 by ramarti2          #+#    #+#             */
/*   Updated: 2025/10/20 13:17:04 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_err(int errnum, int err, char *msg)
{
	if (err == 1)
		printf("cd: %s: %s\n", strerror(errno), msg); // handle_err()
	else
		perror("Error");
	return ;
}
