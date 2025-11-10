/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:45:41 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/12 10:32:13 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	isminus;
	int	num;

	while (*nptr == ' ' || *nptr == '\r' || *nptr == '\t' || *nptr == '\f'
		|| *nptr == '\v' || *nptr == '\n')
		nptr++;
	isminus = 0;
	if (*nptr == '-')
	{
		isminus = 1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num += (*nptr - '0');
		nptr++;
		if (*nptr >= '0' && *nptr <= '9')
			num = num * 10;
	}
	if (isminus == 1)
		return (-num);
	return (num);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("%i\n", ft_atoi("           \n\t\f
			-+00000000000000012300000000abc567"));
}*/
