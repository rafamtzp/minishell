/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:04:06 by gregueir          #+#    #+#             */
/*   Updated: 2025/04/23 11:32:24 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*castdest;
	char	*castsrc;

	if (!dest && !src)
		return (dest);
	i = 0;
	castdest = (char *)(dest);
	castsrc = (char *)(src);
	while (i < n)
	{
		castdest[i] = castsrc[i];
		i++;
	}
	return (dest);
}
