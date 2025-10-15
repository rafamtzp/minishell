/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 11:33:38 by gregueir          #+#    #+#             */
/*   Updated: 2025/04/29 16:01:04 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	is_neg;

	i = 0;
	res = 0;
	is_neg = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg = -1;
		i++;
	}
	while (nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			res = (res * 10) + (nptr[i] - 48);
		else if (nptr[i] < '0' || nptr[i] > '9')
			return (res * is_neg);
		i++;
	}
	return (res * is_neg);
}

/*int	main(void)
{
	char	*n = "-123THERE IS A NYANCAT UNDER YOUR BED";
	printf("%d", ft_atoi(n));
}*/
