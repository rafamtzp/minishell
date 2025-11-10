/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramarti2 <ramarti2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:13:14 by ramarti2          #+#    #+#             */
/*   Updated: 2025/05/09 19:45:40 by ramarti2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	void	*newcontent;

	if (lst == 0 || f == 0 || del == 0)
		return (lst);
	newlst = 0;
	while (lst != 0)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (newnode == 0)
		{
			del(newcontent);
			ft_lstclear(&newlst, del);
			return (0);
		}
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	return (newlst);
}
