#include "push_swap.h"

static void	swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		stack->bottom = first;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	stack->top = second;
}

void	sa(t_ps *ps)
{
	swap(&(ps->a));
	write(1, "sa\n", 3);
}

void	sb(t_ps *ps)
{
	swap(&(ps->b));
	write(1, "sb\n", 3);
}

void	ss(t_ps *ps)
{
	swap(&(ps->a));
	swap(&(ps->b));
	write(1, "ss\n", 3);
}
