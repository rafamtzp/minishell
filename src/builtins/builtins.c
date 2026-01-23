/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/23 16:20:04 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **cmd)
{
	int i;

	i = 1;
	if (!cmd[1])
		printf("\n");
	else if (!cmd[2] && max_strncmp(cmd[1], "-n") == 0)
		printf("");
	else if (max_strncmp(cmd[1], "-n") == 0)
	{
		while (max_strncmp(cmd[i], "-n") == 0)
			i++;
		while (cmd[i])
			printf("%s ", cmd[i++]); // bucle que imprime argumentos sin \n
	}
	else //bucle que imprime argumentos con salto de linea al final
	{
		while(cmd[i])
			printf("%s ", cmd[i++]);
		printf("\n");
	}
}

void	pwd(t_minishell *michi)
{
	t_envar	*pwd;

	pwd = find_envar("PWD", michi->envars);
	if (!pwd)
		michi_exit(michi, false, "pwd");
	printf("%s\n", pwd->value);
}

void	env(t_envar *envars)
{
	write_envars(envars, false);
}

static bool is_number(char *str, t_minishell *michi)
{
	int i;

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

void	michi_exit(t_minishell *michi, bool print_msg, char *err_msg)
{
	int size;
	int status;

	size = cmd_list_size(michi->cmds);
	close_pipe_ends(-1, michi->pfds, size);
	free_pipe_arr(michi->pfds);
	if (michi->pids)
		free(michi->pids);
	clean_env_list(michi);
	if (err_msg && max_strncmp("perror", err_msg) != 0)
		printf("Error: %s\n", err_msg);
	else if (err_msg && max_strncmp("perror", err_msg) == 0)
		perror("Error");
	if (print_msg == true)
		printf("exit\n");
	free(michi->input);
	if (print_msg && is_number(michi->cmds->cmd[1], michi) && !michi->cmds->cmd[2])
		michi->status = ft_atoi(michi->cmds->cmd[1]);
	else if (print_msg && michi->cmds->cmd[1] && michi->cmds->cmd[2])
		michi->status += write(2, "Error: Too many arguments\n", 27);
	free_cmds(&michi->cmds);
	status = michi->status;
	rl_clear_history();
	free(michi);
	exit(status);
}
