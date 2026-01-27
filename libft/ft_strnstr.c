/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:12:02 by gregueir          #+#    #+#             */
/*   Updated: 2026/01/27 13:06:56 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_size;

	if (ft_strlen(little) <= 0)
		return ((char *)(big));
	little_size = ft_strlen(little);
	i = 0;
	j = 0;
	while (i < len && big[i] != '\0')
	{
		while (i < len && big[i] == little[j])
		{
			if (j == (little_size - 1))
				return ((char *)(big + (i - j)));
			i++;
			j++;
			if (big[i] != little[j])
				i = i - j;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
