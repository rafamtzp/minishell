/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:26:42 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/05 15:25:15 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	lenght;
	int	character;

	lenght = ft_strlen(s) + 1;
	character = c % 256;
	i = 0;
	while (i < lenght)
	{
		if (*s == character)
			return ((char *)s);
		s++;
		i++;
	}
	return (0);
}
