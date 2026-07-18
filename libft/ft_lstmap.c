/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 08:52:26 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:16:56 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n_list;
	t_list	*n_node;

	n_list = NULL;
	n_node = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		n_node = ft_lstnew(f(lst->content));
		if (!n_node)
		{
			ft_lstclear(&n_list, del);
			return (NULL);
		}
		ft_lstadd_back(&n_list, n_node);
		lst = lst->next;
	}
	return (n_list);
}
