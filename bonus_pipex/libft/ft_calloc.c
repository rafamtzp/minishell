/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:50:11 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/09 18:07:22 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ptr;
	long long	result;

	if (nmemb != 0 && size != 0)
	{
		result = nmemb * size;
		if (nmemb != result / size)
			return (0);
	}
	ptr = malloc(nmemb * size);
	if (ptr == 0)
		return (0);
	if (nmemb * size == 0)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
#include <stdio.h>

int	main(void)
{
	int *arr = ft_calloc(5, 4);
	for (int i = 0; i < 5; i++)
		printf("%i\n", arr[i]);
	free(arr);
}*/