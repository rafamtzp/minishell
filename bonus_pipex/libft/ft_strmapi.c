/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:02:47 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:52 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*ms;

	len = ft_strlen(s);
	ms = malloc(len + 1);
	if (ms == 0)
		return (0);
	ms[len] = '\0';
	i = 0;
	while (s[i])
	{
		ms[i] = f(i, s[i]);
		i++;
	}
	return (ms);
}

/*
char	func(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z' && i % 2 == 1)
		return ('x');
	return (c);
}
#include <stdio.h>

int	main(void)
{
	char *s = "hello, world";
	printf("%s\n", ft_strmapi(s, func));
}*/
