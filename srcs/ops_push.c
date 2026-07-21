#include "push_swap.h"

#include <unistd.h>

static void	push(t_stack *dest, t_stack *src)
{
	t_node	*to_move;

	if (!src || src->size == 0)
		return ;
	to_move = src->top;
	src->top = src->top->next;
	if (src->top)
		src->top->prev = NULL;
	else
		src->bottom = NULL;
	src->size--;
	to_move->next = dest->top;
	to_move->prev = NULL;
	if (dest->top)
		dest->top->prev = to_move;
	else
		dest->bottom = to_move;
	dest->top = to_move;
	dest->size++;
}

void	pa(t_ps *ps)
{
	push(&ps->a, &ps->b);
	write(1, "pa\n", 3);
}

void	pb(t_ps *ps)
{
	push(&ps->b, &ps->a);
	write(1, "pb\n", 3);
}