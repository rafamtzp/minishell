/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:52:10 by gregueir          #+#    #+#             */
/*   Updated: 2025/04/25 13:49:52 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;
	size_t	target_size;

	src_len = (size_t)(ft_strlen(src));
	if (!dst && size == 0)
		return (size - src_len);
	dst_len = (size_t)(ft_strlen(dst));
	target_size = size - dst_len - 1;
	i = 0;
	if (size <= dst_len)
		return (size + src_len);
	while (i < target_size && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*int	main(void)
{
	char	buff[60] = "Hola"
	char	source[60] = " Buenos días"
	
	printf("%zu, %s",ft_strlcat(buff, source, sizeof(buff)), buff);
}*/
