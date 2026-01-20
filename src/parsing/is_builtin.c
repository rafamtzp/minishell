/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:11 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/20 12:02:48 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_cmd *node)
{
	if (!(node->cmd[0]))
		return (false);
	if (max_strncmp("echo", node->cmd[0]) == 0
		|| max_strncmp("cd", node->cmd[0]) == 0
		|| max_strncmp("pwd", node->cmd[0]) == 0
		|| max_strncmp("export", node->cmd[0]) == 0
		|| max_strncmp("unset", node->cmd[0]) == 0
		|| max_strncmp("env", node->cmd[0]) == 0
		|| max_strncmp("exit", node->cmd[0]) == 0)
		return (true);
	return (false);
}
