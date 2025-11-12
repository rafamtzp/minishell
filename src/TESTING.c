#include "minishell.h"

//------------------ from exit.c in pipex ------------------------------

void	close_pipe_ends(int i, int **pfds, int size)
{
	int	j;

	if (pfds == NULL)
		return ;
	if (i > 0)
		close(pfds[i - 1][WRITE_END]);
	if (i < size - 1 && i > -1) // added size-1 to fix bug
		close(pfds[i][READ_END]);
	j = 0;
	while (j < size - 1)
	{
		if (j != i && j != i - 1)
		{
			close(pfds[j][READ_END]);
			close(pfds[j][WRITE_END]);
		}
		j++;
	}
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (!cmds || !(*cmds))
		return ;
	current = *cmds;
	while (current)
	{
		next = current->next;
		i = 0;
		if (current->delim)
			free(current->delim);
		if (current->path)
			free(current->path);
		while (current->cmd && current->cmd[i])
			free(current->cmd[i++]);
		if (current->cmd)
			free(current->cmd);
		free(current);
		current = next;
	}
	*cmds = NULL;
}

void	free_pipe_arr(int **pfds)
{
	int	i;

	if (!pfds)
		return ;
	i = 0;
	while (pfds[i])
		free(pfds[i++]);
	free(pfds);
}

void	close_first_and_last(t_cmd **cmds)
{
	t_cmd	*ptr;

	if (!cmds || !(*cmds))
		return ;
	ptr = *cmds;
	if (ptr && ptr->infile != STDIN_FILENO && ptr->infile != -1)
		close(ptr->infile);
	while (ptr->next)
		ptr = ptr->next;
	if (ptr->outfile != STDOUT_FILENO && ptr->outfile != -1)
		close(ptr->outfile);
}

void	handle_err(t_cmd **cmds, int **pfds)
{
	perror("Error");
	free_pipe_arr(pfds);
	close_first_and_last(cmds);
	free_cmds(cmds);
	exit(1);
}
// ------------------------------------------------------------------------------------------------

int	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (-1);
}

char	**get_env_paths(void)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
	{
		free_str_arr(paths);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (!paths[i])
		{
			free_str_arr(paths);
			return (NULL);
		}
		i++;
	}
	return (paths);
}

static int	find_paths(t_cmd **cmds)
{
	int		i;
	char	**paths;
	char	*path;
	t_cmd	*ptr;

	paths = get_env_paths();
	ptr = *cmds;
	path = paths[0];
	while (ptr)
	{
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(paths[i], ptr->cmd[0]);
			if (!path)
				return (free_str_arr(paths));
			// free cmds and close files outside
			if (access(path, X_OK) == 0)
				break ;
			free(path);
			path = NULL;
			i++;
		}
		if (!path)
			return (free_str_arr(paths)); // free cmds and close files outside
		ptr->path = path;
		ptr = ptr->next;
	}
	free_str_arr(paths);
	return (0);
}

static void	check_and_store_cmds(int argc, char **argv, t_cmd **cmds)
{
	int		is_heredoc;
	t_cmd	*node;
	int		i;

	// first node case: (could or could not be here_doc)
	// if first parameter is here_doc, is_heredoc = 1;
	is_heredoc = 0;
	if (argc < 3 || (!argv[1][0] || !argv[2][0]))
		// if first args are empty or less than 3
		handle_err(NULL, NULL);
	if (ft_strncmp("here_doc", argv[1], max_strlen("here_doc", argv[1])) == 0)
		is_heredoc = 1;
	i = 2 + is_heredoc; // if isheredoc, argv3 is command instead of argv2
	while (i < argc - 1)
	{
		if (!argv[i][0])
			handle_err(NULL, NULL);
		if (is_heredoc == 1 && i == 3)
			node = cmd_list_new(argv[3], argv[2]);
		// note: in this case we can assume the last arg is always outfile! Not in minishell tho!
		else
			node = cmd_list_new(argv[i], NULL);
		if (!node)
			handle_err(cmds, NULL);
		cmd_list_add_back(cmds, node);
		i++;
	}
}

int	max_strlen(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	return (ft_strlen(s2));
}

// *much simpler than minishell
void	open_and_store_fds(int argc, char **argv, t_cmd **cmds)
{
	t_cmd	*ptr;

	ptr = *cmds;
	while (ptr)
	{
		if (ptr == *cmds && ptr->delim == NULL) // if merely first node,
			ptr->infile = open(argv[1], O_RDONLY);
		if ((*cmds)->delim && ptr->next == NULL)
			// if first node delim and last node, append outfile
			ptr->outfile = open(argv[argc - 1], O_CREAT | O_APPEND | O_RDWR);
		else if (ptr->next == NULL) // if merely last node
			ptr->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
		if (ptr->infile == -1 || ptr->outfile == -1)
			handle_err(cmds, NULL);
		ptr = ptr->next;
	}
}

void	parsing_storing_checking(int argc, char **argv, t_cmd **cmds)
{
	check_and_store_cmds(argc, argv, cmds);
	open_and_store_fds(argc, argv, cmds);
	if (find_paths(cmds) == -1)
	{
		printf("command not found\n"); // free and close
		handle_err(cmds, NULL);
	}
}