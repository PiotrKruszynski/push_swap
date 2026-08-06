/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rrotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkruszyn <pkruszyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:45:12 by pkruszyn          #+#    #+#             */
/*   Updated: 2026/08/06 10:45:12 by pkruszyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_stack *stack)
{
	t_node		*last;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	last = stack->bottom;
	stack->bottom = last->prev;
	stack->bottom->next = NULL;
	last->prev = NULL;
	last->next = stack->top;
	stack->top->prev = last;
	stack->top = last;
}

void	rra(t_ps *ps)
{
	reverse_rotate(&(ps->a));
	ps->total_ops++;
	ps->op_counter[O_RRA]++;
	write(1, "rra\n", 4);
}

void	rrb(t_ps *ps)
{
	reverse_rotate(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_RRB]++;
	write(1, "rrb\n", 4);
}

void	rrr(t_ps *ps)
{
	reverse_rotate(&(ps->a));
	reverse_rotate(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_RRR]++;
	write(1, "rrr\n", 4);
}
