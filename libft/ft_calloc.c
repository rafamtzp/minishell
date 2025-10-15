/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:07:24 by gregueir          #+#    #+#             */
/*   Updated: 2025/04/30 12:00:58 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;

	if (nmemb * size >= (2147483648))
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (arr);
	ft_bzero(arr, (nmemb * size));
	return ((void *)(arr));
}

/*int	main(void)
{
	void	*new_arr;

	new_arr = ft_calloc(4, 5);
	ft_free_arr(new_arr, 5);
}*/
