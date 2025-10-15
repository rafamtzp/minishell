/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:29:12 by gregueir          #+#    #+#             */
/*   Updated: 2025/08/06 11:13:16 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(int n)
{
	long	nbr;
	int		count;

	nbr = n;
	count = 0;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr > 9)
		count += ft_putnbr(nbr / 10);
	count += ft_putchar(nbr % 10 + '0');
	return (count);
}

int	ft_unsigned_putnbr(unsigned int n)
{
	long	nbr;
	int		count;

	nbr = n;
	count = 0;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr *= -1;
	}
	if (nbr > 9)
		count += ft_putnbr(nbr / 10);
	count += ft_putchar(nbr % 10 + '0');
	return (count);
}

int	ft_putstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		count += 6;
	}
	while (s && *s)
	{
		write(1, s, 1);
		count++;
		s++;
	}
	return (count);
}

int	ft_puthex(unsigned long n, const char lower, int is_pointer)
{
	int		count;
	char	minus;

	count = 0;
	if (is_pointer)
	{
		write(1, "0x", 2);
		count += 2;
		is_pointer = 0;
	}
	minus = 'a';
	if (lower == 'X')
		minus = 'A';
	if (n > 15)
		count += ft_puthex(n / 16, lower, is_pointer);
	if (n % 16 > 9)
		count += ft_putchar((n % 16) - 10 + minus);
	else
		count += ft_putchar(n % 16 + '0');
	return (count);
}

