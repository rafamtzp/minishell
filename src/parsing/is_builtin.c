/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:11 by gregueir          #+#    #+#             */
/*   Updated: 2025/12/09 13:52:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_cmd *node)
{
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
