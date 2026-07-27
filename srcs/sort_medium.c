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

static void	cheap_push_back(t_ps *ps, int pos_max, int pos_next)
{
	int	cost_max;
	int	cost_next;

	cost_max = get_cost(pos_max, ps->b.size);
	cost_next = get_cost(pos_next, ps->b.size);
	if (ps->b.size > 1 && pos_next != -1 && cost_next < cost_max)
	{
		rotate_b_to_top(ps, pos_next);
		pa(ps);
		rotate_b_to_top(ps, find_pos_b(&(ps->b), ps->b.size - 1));
		pa(ps);
		sa(ps);
	}
	else
	{
		rotate_b_to_top(ps, pos_max);
		pa(ps);
	}
}

static void	push_back_to_a(t_ps *ps)
{
	int	pos_max;
	int	pos_next;

	while (ps->b.size > 0)
	{
		pos_max = find_pos_b(&(ps->b), ps->b.size - 1);
		if (ps->b.size > 1)
			pos_next = find_pos_b(&(ps->b), ps->b.size - 2);
		else
			pos_next = -1;
		cheap_push_back(ps, pos_max, pos_next);
	}
}

static void	push_to_b(t_ps *ps, int *counter, int chunk_size)
{
	while (ps->a.size > 0)
	{
		if (ps->a.top->index <= *counter)
		{
			pb(ps);
			rb(ps);
			(*counter)++;
		}
		else if (ps->a.top->index < (*counter + chunk_size))
		{
			pb(ps);
			(*counter)++;
		}
		else
			ra(ps);
	}
}

static void	divide_chunks(t_ps *ps)
{
	int	counter;
	int	calculated_chunk;

	counter = 0;
	calculated_chunk = get_chunk_size(ps->a.size);
	push_to_b(ps, &counter, calculated_chunk);
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
