/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:32:43 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/09 15:33:05 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_gen_rand(int min, int max)
{
	int		a;
	int		m;
	int		seed;
	int		fd;
	char	c;

	fd = open("/dev/urandom", O_RDONLY);
	read(fd, &c, 1);
	a = 16807;
	m = __INT_MAX__;
	seed = (a * (unsigned int) c) % (max + 1 - min) + min;
	close(fd);
	return (seed);
}

int	ft_rand(int min, int max)
{
	return (ft_gen_rand(min, max));
}