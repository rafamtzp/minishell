/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:00:02 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:38:55 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		sizecalc(int n);
static int		isnegative(int n);

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				i;
	char			*str;

	str = malloc(sizecalc(n) + isnegative(n) + 1);
	if (str == 0)
		return (0);
	if (isnegative(n) == 1)
	{
		num = -n;
		str[0] = '-';
	}
	else
		num = n;
	str[sizecalc(n) + isnegative(n)] = '\0';
	i = 1 - isnegative(n);
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[sizecalc(n) - i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	return (str);
}

static int	sizecalc(int n)
{
	int				size;
	unsigned int	temp_n;

	if (n < 0)
		temp_n = -n;
	else if (n > 0)
		temp_n = n;
	else
		return (1);
	size = 0;
	while (temp_n > 0)
	{
		temp_n = temp_n / 10;
		size++;
	}
	return (size);
}

static int	isnegative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(-948376));
}*/