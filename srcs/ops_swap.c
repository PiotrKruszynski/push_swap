/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 11:48:26 by kwlodars          #+#    #+#             */
/*   Updated: 2026/08/06 11:48:27 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return ;
	first = stack_pop(stack);
	second = stack_pop(stack);
	stack_add_front(stack, first);
	stack_add_front(stack, second);
}

void	sa(t_ps *ps)
{
	swap(&(ps->a));
	ps->total_ops++;
	ps->op_counter[O_SA]++;
	write(1, "sa\n", 3);
}

void	sb(t_ps *ps)
{
	swap(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_SB]++;
	write(1, "sb\n", 3);
}

void	ss(t_ps *ps)
{
	swap(&(ps->a));
	swap(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_SS]++;
	write(1, "ss\n", 3);
}
