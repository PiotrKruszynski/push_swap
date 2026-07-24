#include "push_swap.h"

//	turk algorithm -mod
// selection sort
static int	find_min_position(t_stack *stack)
{
	t_node	*curr;
	int		min_value;
	int		min_pos;
	int		pos;

	curr = stack->top;
	min_value = curr->value;
	min_pos = 0;
	pos = 0;
	while (curr)
	{
		if (curr->value < min_value)
		{
			min_value = curr->value;
			min_pos = pos;
		}
		curr = curr->next;
		pos++;
	}
	return (min_pos);
}

void	sort_simple(t_ps *ps)
{
	int	min_pos;
	int i;

	while (ps->a.size > 0)
	{
		min_pos = find_min_position(&ps->a);
		if (min_pos <= ps->a.size / 2)
		{
			while (min_pos-- > 0)
				ra(ps);
		}
		else
		{
			i = ps->a.size - min_pos;
			while (i-- > 0)
				rra(ps);
		}
		pb(ps);
	}
	while (ps->b.size > 0)
		pa(ps);
}