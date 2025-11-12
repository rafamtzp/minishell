/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:16:16 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/09 18:37:53 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (dest == 0 && src == 0 && n > 0)
		return (0);
	ptr1 = (unsigned char *)src;
	ptr2 = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		*ptr2 = *ptr1;
		ptr1++;
		ptr2++;
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	//const char *src = "hello, world";
	int src[] = {1, 2, 3, 4, 5};
	int dest[100];
	ft_memcpy(dest, src, 5*4);
	//printf("%s\n", dest);
	for (int i = 0; i < 5; i++)
		printf("%i,\n", src[i]);
}*/