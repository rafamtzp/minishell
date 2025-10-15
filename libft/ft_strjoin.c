/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:03:22 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/05 14:20:59 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*buff;

	buff = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!buff)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		buff[i] = s1[i];
		i++;
	}
	j = i;
	i = 0;
	while (s2[i])
	{
		buff[j] = s2[i];
		i++;
		j++;
	}
	buff[j] = '\0';
	return (buff);
}
