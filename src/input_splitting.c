/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:02:11 by gregueir          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/18 17:24:23 by gregueir         ###   ########.fr       */
=======
/*   Updated: 2025/11/18 17:01:44 by ramarti2         ###   ########.fr       */
>>>>>>> 7162710d4ee245419d5ee46019eac9a5ee7f87da
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *node)
{
	if (max_strncmp("echo", node->cmd[0]) == 0 
	|| max_strncmp("cd", node->cmd[0]) == 0
	|| max_strncmp("pwd", node->cmd[0]) == 0
	|| max_strncmp("export", node->cmd[0]) == 0
	|| max_strncmp("unset", node->cmd[0]) == 0
	|| max_strncmp("env", node->cmd[0]) == 0
	|| max_strncmp("exit", node->cmd[0]) == 0)
		return (true);
	return (false);
}

/*int	cmd_count(char *s)
{
	int	i;
	int	count;
	int	quotes;

	i = 0;
	count = 0;
	if (!*s)
		return (0);
	while (s && s[i])
	{
		if (s[i] == ' ' || !s[i])
		{
			
		}
	}
}*/

int	pipe_finder(char *s)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (*s && s[i])
	{
		if (in_quotes != 0 && (s[i] == '\'' || s[i] == '\"'))
		{
			if (in_quotes < 0 && s[i] == '\'')
				in_quotes++;
			if (in_quotes > 0 && s[i] == '\"')
				in_quotes--;
		}
		else if (in_quotes == 0 && (s[i] == '\'' || s[i] == '\"'))
		{
			if (s[i] == '\'')
				in_quotes--;
			if (s[i] == '\"' && s[i - 1] != '\\')
				in_quotes++;
		}
	}
}

int	input_parsing(t_minishell michi)
{
	int		wcount;
	char	**split;

}
