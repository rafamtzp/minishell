/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:09:20 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:33:28 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	ft_memcpy(ptr, s, len + 1);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	char *s = "hello, world";
	char *dest = ft_strdup(s);
	printf("%s\n", dest);
	free(dest);
}*/