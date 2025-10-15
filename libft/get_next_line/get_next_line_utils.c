/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:50:30 by gregueir          #+#    #+#             */
/*   Updated: 2025/08/06 12:50:07 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_gnl_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (s && *s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
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
	ft_gnl_free(s1);
	return (buff);
}

char	*ft_gnl_strdup(char *src, int init)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(src);
	if (len == 0 && !init)
		return (NULL);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
