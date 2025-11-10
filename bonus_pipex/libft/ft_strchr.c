/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:09:36 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:33:42 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == '\0')
		return (ptr);
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "hello, world";
	char c = '\0';

	printf("s: %p, c in s: %p\n", s, ft_strchr(s, c));
}*/