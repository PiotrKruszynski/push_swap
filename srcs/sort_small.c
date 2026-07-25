#include "push_swap.h"
// dla malych liczb
void	sort_three(t_ps *ps)
{
	int	first;
	int	second;
	int	third;

	if (!ps || ps->a.size < 3)
		return ;
	first = ps->a.top->index;
	second = ps->a.top->next->index;
	third = ps->a.top->next->next->index;
	if (first > second && second < third && first < third)
		sa(ps);
	else if (first > second && second > third)
	{
		sa(ps);
		rra(ps);
	}
	else if (first > second && second < third && first > third)
		ra(ps);
	else if (first < second && second > third && first < third)
	{
		sa(ps);
		ra(ps);
	}
	else if (first < second && second > third && first > third)
		rra(ps);
}


void	push_min_to_b(t_ps *ps, int min_pos, int size)
{
	if (min_pos <= size / 2)
	{
		while (min_pos > 0)
		{
			ra(ps);
			min_pos--;
		}
	}
	else
	{
		while (min_pos < size)
		{
			rra(ps);
			min_pos++;
		}
	}
	pb(ps);
}

void	sort_small(t_ps *ps, int size)
{
	int	pushed;

	if (!ps || size <= 1)
		return ;
	if (size == 2 && ps->a.top->index > ps->a.top->next->index)
		sa(ps);
	if (size <= 3)
	{
		if (size == 3)
			sort_three(ps);
		return ;
	}
	pushed = 0;
	while (size - pushed > 3)
	{
		push_min_to_b(ps, find_min_position(&(ps->a), size - pushed), size - pushed);
		pushed++;
	}
	sort_three(ps);
	while (pushed-- > 0)
		pa(ps);
}