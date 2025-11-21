/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:17:01 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/21 13:44:43 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_err(t_minishell *michi, char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	else
		perror("Error");
	michi_exit(michi, false, NULL);
}
