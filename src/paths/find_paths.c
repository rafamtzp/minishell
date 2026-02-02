/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:17:59 by gregueir          #+#    #+#             */
/*   Updated: 2026/02/02 17:01:31 by ramarti2         ###   ########.fr       */
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
	t_envar	*pathvar;

	pathvar = find_envar("PATH", michi->envars);
	if (!pathvar)
		return (NULL);
	paths = ft_split(pathvar->value, ':');
	if (!paths)
		return (NULL);
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
		if (ptr->cmd[0] && access(ptr->cmd[0], X_OK) == 0)
			ptr->path = ft_strdup(ptr->cmd[0]);
		else if (paths)
			search_paths(ptr, paths);
		printf("%s\n", ptr->path);
		ptr = ptr->next;
	}
	if (paths)
		free_str_arr(paths);
}
