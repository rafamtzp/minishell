#include "../minishell.h"

char 		**env_list_to_arr(t_envar *env)
{
	char **env_arr;
	char *tmp;
	int i;

	env_arr = malloc((env_list_size(env) + 1) * sizeof(char *));
	if (!env_arr)
		exit(1); // TODO
	env_arr[env_list_size(env)] = NULL;
	i = 0;
	while (env)
	{
		if (env && !env->varname)
			exit(1); // TODO
		tmp = ft_strjoin(env->varname, "=");
		if (env->value)
			env_arr[i] = ft_strjoin(tmp, env->value);
		else
			env_arr[i] = env->varname;
		free(tmp);
		i++;
		env = env->next;
	}
	return (env_arr);
}

void	builtin_execve(char **cmd, t_minishell *michi)
{
	if (max_strncmp(cmd[0], "echo") == 0)
		echo(cmd);
	else if (max_strncmp(cmd[0], "pwd") == 0)
		pwd(michi);
	else if (max_strncmp(cmd[0], "env") == 0)
		env(michi->envars);
	else if (max_strncmp(cmd[0], "exit") == 0 && cmd_list_size(michi->cmds) == 1)
		michi_exit(michi, true);
	michi_exit(michi, false);
}

bool	unforked_execve(char **cmd, t_minishell *michi)
{
	bool executed;
	//int stdout; // to be continued.....
	executed = true;
	if (max_strncmp(cmd[0], "cd") == 0) // sin fork // no escribe ni recibe
		michi->status = cd(cmd, michi);
	else if (max_strncmp(cmd[0], "export") == 0) // sin fork // escribe pero no recibe
		michi->status = export(michi, cmd);
	else if (max_strncmp(cmd[0], "unset") == 0) // sin fork // ni escribe ni recibe
		michi->status = unset(&michi->envars, cmd);
	else
		executed = false;
	return (executed);
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
	char **env;
	int		i;
	bool	executed_unforked;
	int stdout_copy;

	ptr = michi->cmds;
	i = 0;
	stdout_copy = dup(STDOUT_FILENO);
	while (ptr)
	{
		dup2(ptr->outfile, STDOUT_FILENO);
		executed_unforked = unforked_execve(ptr->cmd, michi);
		dup2(stdout_copy, STDOUT_FILENO);
		michi->pids[i] = fork();
		if (michi->pids[i] == 0)
		{
			if (executed_unforked == true)
				michi_exit(michi, false);
			dup2(ptr->outfile, STDOUT_FILENO);
			if (ptr->delim)
				start_heredoc(ptr);
			dup2(ptr->infile, STDIN_FILENO);
			close_pipe_ends(i, michi->pfds, cmd_list_size(michi->cmds));
            if (is_builtin(ptr) == true)
                builtin_execve(ptr->cmd, michi);
			env = env_list_to_arr(michi->envars);
			if (!env)
			{
				write(2, "failed to create char **env\n", 29);
				exit(1);
			}
			execve(ptr->path, ptr->cmd, env);
			printf("%s: command not found\n", ptr->cmd[0]);
			exit(1);
		}
		i++;
		ptr = ptr->next;
	}
}
