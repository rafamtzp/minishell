/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:18:48 by ramarti2          #+#    #+#             */
/*   Updated: 2025/11/10 13:59:50 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: make echo $? print exit status of last command!!!!!!!!!!!!
void	echo(char *msg, bool newline)
{
	if (newline == true)
		printf("%s\n", msg);
	else
		printf("%s", msg);
}
/*
Note: cd should change the working directory of a process!!!
But, it doesn't change the working directory of the current shell.
Because when the program is executed in the shell,
the shell follows fork on exec mechanism.
So, it doesn't affect the current shell.
*/

// way more complicated.........
// TODO: update OLDPWD
// TODO: update PWD
// maybe implement 'cd -'?
void	cd(t_cmd **cmd)
{
	if (chdir((*cmd)->cmd[1]) != 0)
		handle_err(errno, 1, "filename");
}

void	pwd(void)
{
	char	*buf;

	buf = ft_calloc(1, PATH_MAX);
	if (!buf)
		handle_err(errno, 2, "");
	getcwd(buf, PATH_MAX);
	if (!buf)
	{
		perror("Error");
		return ;
	}
	
	printf("%s\n", getcwd(buf, PATH_MAX));
}

void	env(t_envar **envars)
{
	write_envars(*envars, true);
}

void	michi_exit(void)
{
	// Do later bc it may involve shutting down multiple processes
	return ;
}
