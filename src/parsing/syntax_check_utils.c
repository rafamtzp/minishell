/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:52:59 by gregueir          #+#    #+#             */
/*   Updated: 2025/11/24 16:36:40 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_filename(char *s)
{
	
}

int	syntax_check_redirect(char *s)
{
	int	i;

	i = 0;
	while(s && s[i])
	{
		if (s[i] == '"')
			i += i + (dquote_checker(s + i));
		else if (s[i] == '\'')
			i += i + (squote_checker(s + i));
		else if (s[i] == '>')
		{
			
		}
		i++;
	}
	return (0);
}
