/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 08:52:03 by kwlodars          #+#    #+#             */
/*   Updated: 2026/07/05 14:16:25 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*next_nd;

	if (!lst || !*lst || !del)
	{
		return ;
	}
	current = *lst;
	while (current != NULL)
	{
		next_nd = current->next;
		ft_lstdelone(current, del);
		current = next_nd;
	}
	*lst = NULL;
}
