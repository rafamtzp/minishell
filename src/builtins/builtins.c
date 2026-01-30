/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/30 16:25:11 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **cmd)
{
	int	i;

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
			printf("%s ", cmd[i++]);
	}
	else
	{
		while (cmd[i])
			printf("%s ", cmd[i++]);
		printf("\n");
	}
}

void	pwd(t_minishell *michi)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
	{
		if (!michi->pwd)
			michi_exit(michi, false, "Info on cwd not found");
		printf("%s\n", michi->pwd);
		return ;
	}
	printf("%s\n", buf);
}

void	env(t_envar *envars)
{
	write_envars(envars, false);
}
