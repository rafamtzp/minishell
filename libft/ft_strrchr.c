/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:57:12 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/05 15:26:30 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	character;

	i = ft_strlen(s);
	character = (char)(c);
	while (i != -1)
	{
		if (s[i] == character)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
