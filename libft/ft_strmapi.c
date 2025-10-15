/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:50:43 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/07 10:57:07 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*buf;

	i = 0;
	len = ft_strlen(s);
	buf = ft_calloc(sizeof(char), len + 1);
	if (!buf)
		return (NULL);
	while (i < len)
	{
		buf[i] = f(i, s[i]);
		i++;
	}
	return (buf);
}
