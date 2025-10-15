/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:46:40 by gregueir          #+#    #+#             */
/*   Updated: 2025/04/29 11:19:07 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)(s1);
	str2 = (unsigned char *)(s2);
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	i--;
	return (str1[i] - str2[i]);
}

/*int	main(void)
{
	char	*s1 = "abcd";
	char	*s2 = "abcde";

	printf("%d", ft_memcmp(s1, s2, 4));
	return (0);
}*/
