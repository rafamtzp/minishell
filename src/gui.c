/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:07:30 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/29 15:44:48 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cat(void)
{
	int		fd;
	char	*line;
	char	*cat;
	int		catno;
	int		i;

	catno = ft_rand(1, 9);
	cat = ft_strdup("./cats/cat0X.txt");
	i = 0;
	while (*cat && cat[i] != 'X')
		i++;
	cat[i] = catno + '0';
	fd = open(cat, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	free(cat);
	close(fd);
}
