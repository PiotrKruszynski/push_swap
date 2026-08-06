/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkruszyn <pkruszyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:45:20 by pkruszyn          #+#    #+#             */
/*   Updated: 2026/08/06 11:05:40 by pkruszyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rotate(t_stack *stack)
{
    t_node  *first;

    if(!stack || !stack->top || !stack->top->next)
        return ;
    first = stack->top;
    stack->top = first->next;
    stack->top->prev = NULL;
    first->next = NULL;
    first->prev = stack->bottom;
    stack->bottom->next = first;
    stack->bottom = first;
}

void	ra(t_ps *ps)
{
	rotate(&(ps->a));
	ps->total_ops++;
	ps->op_counter[O_RA]++;
	write(1, "ra\n", 3);
}

void	rb(t_ps *ps)
{
	rotate(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_RB]++;
	write(1, "rb\n", 3);
}

void	rr(t_ps *ps)
{
	rotate(&(ps->a));
	rotate(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_RR]++;
	write(1, "rr\n", 3);
}
