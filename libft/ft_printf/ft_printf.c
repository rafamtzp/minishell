/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:31:31 by gregueir          #+#    #+#             */
/*   Updated: 2025/06/16 13:10:28 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_null_pointer(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		count += 5;
	}
	else
		count += ft_puthex((unsigned long)ptr, 'x', 1);
	return (count);
}

static int	ft_conversion_parser(const char c, va_list list)
{
	if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (c == 'p')
		return (ft_null_pointer(va_arg(list, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (c == 'u')
		return (ft_unsigned_putnbr((unsigned int)(va_arg(list, int))));
	else if (c == 'x')
		return (ft_puthex(va_arg(list, unsigned int), 'x', 0));
	else if (c == 'X')
		return (ft_puthex(va_arg(list, unsigned int), 'X', 0));
	else if (c == '%')
		write(1, "%", 1);
	else
		return (0);
	return (1);
}

static int	ft_format_parser(const char *form, va_list list)
{
	int	count;

	count = 0;
	while (form && *form)
	{
		if (*form == '%')
		{
			count += ft_conversion_parser(form[1], list);
			form++;
		}
		else
		{
			write(1, &form[0], 1);
			count++;
		}
		form++;
	}
	return (count);
}

int	ft_printf(const char *form, ...)
{
	va_list	list;
	int		count;

	va_start(list, form);
	count = ft_format_parser(form, list);
	va_end(list);
	return (count);
}
