/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:37:26 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/07 11:41:01 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	ft_intlen(long n)
{
	unsigned long	len;

	len = 0;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

static char	*ft_itoa_aux(char *buf, unsigned long n, unsigned long len, int neg)
{
	unsigned long	i;

	i = 1;
	if (neg == 1)
		i = 0;
	else
		neg = 0;
	buf[len + i] = '\0';
	while (len >= 1)
	{
		buf[(len--) - neg] = (n % 10) + '0';
		n /= 10;
	}
	return (buf);
}

char	*ft_itoa(int n)
{
	int				is_neg;
	long			num;
	unsigned long	len;
	char			*buf;

	num = (long)(n);
	is_neg = 1;
	if (n < 0)
		is_neg = -1;
	num *= is_neg;
	len = ft_intlen(num);
	if (is_neg == -1)
	{
		buf = malloc(sizeof(char) * (len + 2));
		if (!buf)
			return (0);
		buf[0] = '-';
	}
	else
	{
		buf = malloc(sizeof(char) * (len + 1));
		if (!buf)
			return (0);
	}
	return (ft_itoa_aux(buf, num, len, is_neg));
}

/*int	main(void)
{
	printf("%lu", ft_intlen(79274));
}*/
