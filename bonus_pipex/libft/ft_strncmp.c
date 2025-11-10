/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:49:32 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:48 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0' || *s2 == '\0')
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int ft_strncmp(const char *s1, const char *s2, size_t n);
int main(void)
{
    char *s1 = "abcdef";
    char *s2 = "abc\375xx";
    unsigned int n = 5;
    printf("%i\n", ft_strncmp(s1, s2, n));
    printf("%i\n", strncmp(s1, s2, n));
}*/