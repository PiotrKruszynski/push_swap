/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium_v1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 10:46:20 by kwlodars          #+#    #+#             */
/*   Updated: 2026/08/06 11:53:18 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_chunk_size(int size)
{
	if (size <= 20)
		return (size / 2);
	if (size <= 100)
		return (size / 5);
	return (size / 11);
}

void	push_back_to_a(t_ps *ps)
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

void	push_to_b(t_ps *ps, int min_chunk, int max_chunk)
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

void	divide_chunks(t_ps *ps)
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
	if (ps->a.size <= 5)
		sort_small(ps, ps->a.size);
	else
		divide_chunks(ps);
}
