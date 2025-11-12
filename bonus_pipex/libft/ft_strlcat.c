/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:05:52 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:33:17 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	srclen = ft_strlen(src);
	dstlen = 0;
	i = 0;
	while (dst[i] && i < size)
	{
		dstlen++;
		i++;
	}
	if (dst[i] || size == 0)
		return (size + srclen);
	while (i < size - 1 && *src)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	dst[i] = '\0';
	return (srclen + dstlen);
}
// if strlcat traverses size chars without finding NUL,
	//length of the string is size
/*
#include <stdio.h>

int	main(void)
{
	char dst[100] = "hello, ";
	char *src = "world";
	printf("resulting string has %zu chars\n", ft_strlcat(dst, src, 2));
	printf("%s\n", dst);
}*/