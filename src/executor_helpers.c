#include "minishell.h"

char 		**env_list_to_arr(t_envar *env)
{
	// TODO
	return (NULL);
}

void	builtin_execve(char **cmd, t_minishell *michi)
{
	if (max_strncmp(cmd[0], "echo") == 0)
		echo(cmd);
	else if (max_strncmp(cmd[0], "cd") == 0)
		cd(cmd, michi);
	else if (max_strncmp(cmd[0], "pwd") == 0)
		pwd(michi->envars);
	else if (max_strncmp(cmd[0], "export") == 0)
		export(michi, cmd);
	else if (max_strncmp(cmd[0], "unset") == 0)
		unset(&michi->envars, cmd);
	else if (max_strncmp(cmd[0], "env") == 0)
		env(michi->envars);
	michi_exit(michi, false);
}


static void	start_heredoc(t_cmd *ptr)
{
	int		hfd[2];
	char	*line;

	pipe(hfd);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (max_strncmp(line, ptr->delim) == 0)
		{
			close(hfd[WRITE_END]);
			break ;
		}
		write(hfd[WRITE_END], line, ft_strlen(line));
		ptr->infile = hfd[READ_END];
	}
}

void	start_children(t_minishell *michi)
{
	t_cmd	*ptr;
	int		i;

	ptr = michi->cmds;
	i = 0;
	while (ptr)
	{
		michi->pids[i] = fork();
		if (michi->pids[i] == 0)
		{
			dup2(ptr->outfile, STDOUT_FILENO);
			if (ptr->delim)
				start_heredoc(ptr);
			dup2(ptr->infile, STDIN_FILENO);
			close_pipe_ends(i, michi->pfds, cmd_list_size(michi->cmds));
            if (is_builtin(ptr->cmd) == true)
                builtin_execve(ptr->cmd, michi);
			execve(ptr->path, ptr->cmd, env_list_to_arr(env));
			exit(1);
		}
		i++;
		ptr = ptr->next;
	}
}
