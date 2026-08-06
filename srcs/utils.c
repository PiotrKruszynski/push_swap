/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkruszyn <pkruszyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:45:46 by kwlodars          #+#    #+#             */
/*   Updated: 2026/08/06 11:14:09 by pkruszyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* dodatkowe funkcje */
int	is_sorted(t_stack *stack)
{
	t_node  *curr;

	if (!stack || stack->size < 2)
		return (1);
	curr = stack->top;
	while (curr->next)
	{
		if (curr->value > curr->next->value)
			return (0);
		curr = curr->next;
	}
	return (1);
}

void	indexing_stack(t_ps *ps)
{
	t_node	*current;
	t_node	*compare;
	int		calculated_index;

	if (!ps || !ps->a.top)
		return ;
	current = ps->a.top;
	while (current != NULL)
	{
		calculated_index = 0;
		compare = ps->a.top;
		while (compare != NULL)
		{
			if (compare->value < current->value)
				calculated_index++;
			compare = compare->next;
		}
		current->index = calculated_index;
		current = current->next;
	}
}

int	find_min_position(t_stack *stack, int size)
{
	t_node	*current;
	int		min_index;
	int		min_pos;
	int		pos;

	if (!stack || !stack->top || size <= 0)
		return (-1);
	current = stack->top;
	min_index = current->index;
	min_pos = 0;
	pos = 0;
	while (current && pos < size)
	{
		if (current->index < min_index)
		{
			min_index = current->index;
			min_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (min_pos);
}
