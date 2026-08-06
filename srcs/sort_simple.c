/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkruszyn <pkruszyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:45:46 by pkruszyn          #+#    #+#             */
/*   Updated: 2026/08/06 11:43:29 by pkruszyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//	turk algorithm -mod
// selection sort
static int	find_min_position_simple(t_stack *stack)
{
	t_node	*curr;
	int		min_value;
	int		min_pos;
	int		pos;

	curr = stack->top;
	min_value = curr->value;
	min_pos = 0;
	pos = 0;
	while (curr)
	{
		if (curr->value < min_value)
		{
			min_value = curr->value;
			min_pos = pos;
		}
		curr = curr->next;
		pos++;
	}
	return (min_pos);
}

static void	rotate_min_to_top(t_ps *ps, int min_pos)
{
	int	i;

	if (min_pos <= ps->a.size / 2)
	{
		while (min_pos-- > 0)
			ra(ps);
	}
	else
	{
		i = ps->a.size - min_pos;
		while (i-- > 0)
			rra(ps);
	}
}

void	sort_simple(t_ps *ps)
{
	int	min_pos;

	if (ps->a.size <= 5)
	{
		sort_small(ps, ps->a.size);
		return ;
	}
	while (ps->a.size > 0)
	{
		min_pos = find_min_position_simple(&ps->a);
		rotate_min_to_top(ps, min_pos);
		if (is_sorted(&ps->a))
			break ;
		pb(ps);
	}
	while (ps->b.size > 0)
		pa(ps);
}
