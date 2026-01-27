/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:17:59 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/27 16:39:48 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**get_env_paths(t_minishell *michi)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(find_envar("PATH", michi->envars)->value, ':');
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

static void	search_paths(t_cmd *ptr, char **paths)
{
	int	i;

	i = 0;
	while (paths[i] && is_builtin(ptr) == false)
	{
		if (ptr->cmd[0])
			ptr->path = ft_strjoin(paths[i], ptr->cmd[0]);
		if (!ptr->path)
			break ;
		if (access(ptr->path, X_OK) == 0)
			break ;
		free(ptr->path);
		ptr->path = NULL;
		i++;
	}
}

void	find_paths(t_cmd *ptr, t_minishell *michi)
{
	char	**paths;

	paths = get_env_paths(michi);
	while (ptr)
	{
		if (access(ptr->cmd[0], X_OK) == 0)
			ptr->path = ft_strdup(ptr->cmd[0]);
		else
			search_paths(ptr, paths);
		ptr = ptr->next;
	}
	free_str_arr(paths);
}
