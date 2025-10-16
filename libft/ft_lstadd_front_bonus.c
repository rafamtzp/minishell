/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:28:17 by gregueir          #+#    #+#             */
/*   Updated: 2025/10/15 17:23:41 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!lst)
		return ;
	else
	{
		new -> next = *lst;
		*lst = new;
	}
}

/*int	main(void)
{
	t_list	*node2;
	t_list	*node1;
	t_list	*current;

	node2 = ft_lstnew("Mundo");
	node1 = ft_lstnew("Hola");
	ft_lstadd_front(&node2, node1);
	current = node1;
	while (current -> next != NULL)
	{
		printf("%s\n", (char*)current -> content);
		current = current -> next;
	}
	printf("%s\n", (char*)current -> content);
	free(node2);
	free(node1);
	return (0);
}*/
