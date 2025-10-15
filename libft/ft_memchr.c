/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:08:00 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/06 09:48:23 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*buff;
	int		character;

	i = 0;
	character = (char)(c);
	buff = (char *)(s);
	while (i < n)
	{
		if (*buff == character)
			return (buff);
		buff++;
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char *toprint;

	toprint = (char *)(ft_memchr("Hola", '\0', 5));
	printf("%c", *toprint);
}*/
