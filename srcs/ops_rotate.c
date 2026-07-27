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
// static void	rotate(t_stack *stack)
// {
// 	t_node	*first;

// 	if (!stack || stack->size < 2)
// 		return ;
// 	first = stack_pop(stack);
// 	if (first)
// 		stack_add_back(stack, first);
// }

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
