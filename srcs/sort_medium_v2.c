/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:46:20 by kwlodars          #+#    #+#             */
/*   Updated: 2026/08/06 11:06:34 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

void	rotate_b_to_top(t_ps *ps, int pos)
{
	if (pos <= ps->b.size / 2)
	{
		while (pos > 0)
		{
			rb(ps);
			pos--;
		}
	}
	else
	{
		while (pos < ps->b.size)
		{
			rrb(ps);
			pos++;
		}
	}
}
int	find_pos_b(t_stack *stack, int target_index)
{
	t_node	*current;
	int		pos;

	pos = 0;
	current = stack->top;
	while (current)
	{
		if (current->index == target_index)
			return (pos);
		pos++;
		current = current->next;
	}
	return (-1);
}

void	cheap_push_back(t_ps *ps, int pos_max, int pos_next, int *target_max)
{
	int	cost_max;
	int	cost_next;

	cost_max = get_cost(pos_max, ps->b.size);
	cost_next = get_cost(pos_next, ps->b.size);
	if (ps->b.size > 1 && pos_next != -1 && cost_next < cost_max)
	{
		rotate_b_to_top(ps, pos_next);
		pa(ps);
		rotate_b_to_top(ps, find_pos_b(&(ps->b), *target_max));
		pa(ps);
		sa(ps);
		*target_max -= 2;
	}
	else
	{
		rotate_b_to_top(ps, pos_max);
		pa(ps);
		*target_max -= 1;
	}
}
