/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:56:25 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:30 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start + len > ft_strlen(s) && start < ft_strlen(s))
		len = ft_strlen(s + start);
	else if (start >= ft_strlen(s))
		len = 0;
	sub = ft_calloc(len + 1, 1);
	if (sub == 0)
		return (0);
	i = start;
	if (len == 0)
		return (sub);
	while (s[i] != '\0' && (i - start) < len)
	{
		sub[i - start] = s[i];
		i++;
	}
	return (sub);
}
/*
#include <stdio.h>

int	main(void)
{
	char const *s = "hello, world xxxxxx";
	unsigned int start = 7;
	size_t len = 5;
	printf("%s\n", ft_substr(s, start, len));
}*/