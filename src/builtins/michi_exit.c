/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   michi_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:35:50 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/30 16:29:38 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_number(char *str, t_minishell *michi)
{
	int	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			michi->status = 2;
			write(2, "Error: numeric argument required\n", 34);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	clean_michi(t_minishell *michi)
{
	int	size;

	size = cmd_list_size(michi->cmds);
	close_pipe_ends(-1, michi->pfds, size);
	free_pipe_arr(michi->pfds);
	if (michi->pids)
		free(michi->pids);
	clean_env_list(michi);
	free(michi->input);
	free_cmds(&michi->cmds);
	rl_clear_history();
	if (michi->pwd)
		free(michi->pwd);
	free(michi);
}

void	michi_exit(t_minishell *michi, bool print_msg, char *err_msg)
{
	int	status;

	if (err_msg)
		status = printf("Error: %s\n", err_msg);
	if (print_msg == true)
		printf("exit\n");
	if (print_msg && is_number(michi->cmds->cmd[1], michi)
		&& !michi->cmds->cmd[2])
		michi->status = ft_atoi(michi->cmds->cmd[1]);
	else if (print_msg && michi->cmds->cmd[1] && michi->cmds->cmd[2])
		michi->status += write(2, "Error: Too many arguments\n", 27);
	status = michi->status;
	clean_michi(michi);
	exit(status);
}
