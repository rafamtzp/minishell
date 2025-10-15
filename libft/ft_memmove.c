/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:07:42 by gregueir          #+#    #+#             */
/*   Updated: 2025/04/23 14:58:54 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*castdest;
	char	*castsrc;

	i = 0;
	castdest = (char *)(dest);
	castsrc = (char *)(src);
	if (src < dest)
	{
		while (n)
		{
			castdest[n - 1] = castsrc[n - 1];
			n--;
		}
	}
	else if (dest < src)
	{
		while (i < n)
		{
			castdest[i] = castsrc[i];
			i++;
		}
	}
	return (dest);
}
