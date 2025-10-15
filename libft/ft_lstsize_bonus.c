/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregueir <gregueir@student.42malaga.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:22:02 by gregueir          #+#    #+#             */
/*   Updated: 2025/05/08 10:22:00 by gregueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}

/*int	main(void)
{
	t_list	*node2;
	t_list	*node1;
	t_list	**first;

	node2 = ft_lstnew("Mundo");
	node1 = ft_lstnew("Hola");
	first = &node2;
	ft_lstadd_front(first, node1);
	printf("|%d\n", ft_lstsize(node1));
	free(node2);
	free(node1);
	return (0);
}*/
