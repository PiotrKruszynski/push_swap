#include "push_swap.h"

#include <unistd.h>

static void	push(t_stack *dest, t_stack *src)
{
	t_node	*to_move;

	to_move = stack_pop(src);
	if (!to_move)
		return ;
	stack_add_front(dest, to_move);
}

void	pa(t_ps *ps)
{
	push(&ps->a, &ps->b);
	ps->total_ops++;
	ps->op_counter[O_PA]++;
	write(1, "pa\n", 3);
}

void	pb(t_ps *ps)
{
	push(&ps->b, &ps->a);
	ps->total_ops++;
	ps->op_counter[O_PB]++;
	write(1, "pb\n", 3);
}