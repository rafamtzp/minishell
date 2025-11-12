/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:57:34 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:39 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = 0;
	while (*s)
	{
		if (*s == (char)c)
			ptr = (char *)s;
		s++;
	}
	if ((char)c == '\0')
	{
		ptr = (char *)s;
		return (ptr);
	}
	return (ptr);
}

/*
#include <stdio.h>
int	main(void)
{
	char *s = "helloh";
	char c = 'w';

	printf("s: %p, c in s: %p\n", s, ft_strrchr(s, c));
}*/