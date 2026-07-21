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
	write(1, "rra\n", 4);
}

void	rrb(t_ps *ps)
{
	reverse_rotate(&(ps->b));
	write(1, "rrb\n", 4);
}

void	rrr(t_ps *ps)
{
	reverse_rotate(&(ps->a));
	reverse_rotate(&(ps->b));
	write(1, "rrr\n", 4);
}

