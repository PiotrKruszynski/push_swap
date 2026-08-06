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

void		// debug_print(&ps.a);
	// ft_putnbr_fd(compute_disorder(&ps.a), 1);
	// write(1, "\n", 1);ss(t_ps *ps)
{
	swap(&(ps->a));
	swap(&(ps->b));
	ps->total_ops++;
	ps->op_counter[O_SS]++;
	write(1, "ss\n", 3);
}
