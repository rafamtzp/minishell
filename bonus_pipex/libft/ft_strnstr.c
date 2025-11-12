/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:58:37 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:43 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	j;

	if (*little == '\0')
		return ((char *)big);
	ptr = 0;
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && little[j] && i + j < len)
			j++;
		if (j == ft_strlen(little))
		{
			ptr = (char *)&big[i];
			return (ptr);
		}
		i++;
	}
	return (ptr);
}
/*
#include <stdio.h>
int	main(void)
{
	// const char *big = "hellowwaldoaaafxyz";
	// const char *little = "waldo";
	const char *big = "aaxx";
	const char *little = "xx";
	printf("Address of big: %p \nAddress of little in big: %p\n", big,
		ft_strnstr(big, little, 3));
	printf("%s\n", ft_strnstr(big, little, 5));
}*/