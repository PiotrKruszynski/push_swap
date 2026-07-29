#include "push_swap.h"

static int	get_chunk_size(int size)
{
	if (size <= 20)
		return (size / 2);
	if (size <= 100)
		return (size / 5);
	return (size / 11);
}

static int	get_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

static void	rotate_b_to_top(t_ps *ps, int pos)
{
	if (pos <= ps->b.size / 2)
	{
		while (pos > 0)
		{
			rb(ps);
			pos--;
		}
	}
	else
	{
		while (pos < ps->b.size)
		{
			rrb(ps);
			pos++;
		}
	}
}
static int	find_pos_b(t_stack *stack, int target_index)
{
	t_node	*current;
	int		pos;

	pos = 0;
	current = stack->top;
	while (current)
	{
		if (current->index == target_index)
			return (pos);
		pos++;
		current = current->next;
	}
	return (-1);
}

static void	cheap_push_back(t_ps *ps, int pos_max, int pos_next, int *target_max)
{
	int	cost_max;
	int	cost_next;

	cost_max = get_cost(pos_max, ps->b.size);
	cost_next = get_cost(pos_next, ps->b.size);
	if (ps->b.size > 1 && pos_next != -1 && cost_next < cost_max)
	{
		rotate_b_to_top(ps, pos_next);
		pa(ps);
		rotate_b_to_top(ps, find_pos_b(&(ps->b), *target_max));
		pa(ps);
		sa(ps);
		*target_max -= 2;
	}
	else
	{
		rotate_b_to_top(ps, pos_max);
		pa(ps);
		*target_max -= 1;
	}
}

static void	push_back_to_a(t_ps *ps)
{
	int	pos_max;
	int	pos_next;
	int	target_max;

	target_max = ps->b.size - 1;
	while (ps->b.size > 0)
	{
		pos_max = find_pos_b(&(ps->b), target_max);
		if (ps->b.size > 1 && target_max > 0)
			pos_next = find_pos_b(&(ps->b), target_max - 1);
		else
			pos_next = -1;
		cheap_push_back(ps, pos_max, pos_next, &target_max);
	}
}

static void	push_to_b(t_ps *ps, int min_chunk, int max_chunk)
{
	int	size_to_push;
	
	size_to_push = max_chunk - min_chunk + 1;
	while (size_to_push > 0 && ps->a.size > 0)
	{
		if (ps->a.top->index >= min_chunk && ps->a.top->index <= max_chunk)
		{
			if (ps->a.top->index <= (min_chunk + max_chunk) / 2)
			{
				pb(ps);
				rb(ps);
			}
			else
				pb(ps);
			size_to_push--;
		}
		else
			ra(ps);
	}
}

static void	divide_chunks(t_ps *ps)
{
	int	chunk_size;
	int	min_chunk;
	int	max_chunk;
	int	total_size;

	total_size = ps->a.size;
	chunk_size = get_chunk_size(total_size);
	min_chunk = 0;
	while (min_chunk < total_size)
	{
		max_chunk = min_chunk + chunk_size - 1;
		if (max_chunk >= total_size)
			max_chunk = total_size - 1;
		push_to_b(ps, min_chunk, max_chunk);
		min_chunk += chunk_size;
	}
	push_back_to_a(ps);
}


void	sort_medium(t_ps *ps)
{
	if (ps->a.size <= 3)
		sort_three(ps);
	else if (ps->a.size <= 5)
		sort_small(ps, ps->a.size);
	else
		divide_chunks(ps);
}
