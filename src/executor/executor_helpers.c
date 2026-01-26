/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 13:16:22 by ramarti2          #+#    #+#             */
/*   Updated: 2026/01/26 16:00:49 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char 		**env_list_to_arr(t_envar *env)
{
	char **env_arr;
	char *tmp;
	int i;

	env_arr = malloc((env_list_size(env) + 1) * sizeof(char *));
	if (!env_arr)
		return (NULL);
	env_arr[env_list_size(env)] = NULL;
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->varname, "=");
		if (env->value)
			env_arr[i] = ft_strjoin(tmp, env->value);
		else
			env_arr[i] = ft_strdup(tmp);
		free(tmp);
		if (!env_arr[i])
        {
            while (i-- > 0)
                free(env_arr[i]);
            free(env_arr);
            return (NULL);
        }
		i++;
		env = env->next;
	}
	return (env_arr);
}

void	builtin_execve(t_cmd *ptr, t_minishell *michi)
{
	if (ptr->infile != STDIN_FILENO)
		close(ptr->infile);
	if (max_strncmp(ptr->cmd[0], "echo") == 0)
		echo(ptr->cmd);
	else if (max_strncmp(ptr->cmd[0], "pwd") == 0)
		pwd(michi);
	else if (max_strncmp(ptr->cmd[0], "env") == 0)
		env(michi->envars);
	else if (max_strncmp(ptr->cmd[0], "cd") == 0)
		michi->status = cd(ptr->cmd, michi);
	else if (max_strncmp(ptr->cmd[0], "export") == 0)
		michi->status = export(michi, ptr->cmd);
	else if (max_strncmp(ptr->cmd[0], "unset") == 0)
		michi->status = unset(&michi->envars, ptr->cmd);
	else if (max_strncmp(ptr->cmd[0], "exit") == 0 && cmd_list_size(michi->cmds) == 1)
		michi_exit(michi, true, NULL);
	if (cmd_list_size(michi->cmds) > 1)
		michi_exit(michi, false, NULL);
}

void	start_children(t_minishell *michi)
{
	t_cmd	*ptr;
	int		i;

	write_heredocs(michi);
	ptr = michi->cmds;
	i = 0;
	while (ptr)
	{
		michi->pids[i] = fork();
		if (michi->pids[i] == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			dup2(ptr->outfile, STDOUT_FILENO);
			dup2(ptr->infile, STDIN_FILENO);
			close_pipe_ends(i, michi->pfds, cmd_list_size(michi->cmds));
			exec(ptr, michi);
		}
		i++;
		ptr = ptr->next;
	}
}
