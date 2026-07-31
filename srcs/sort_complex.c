#include "push_swap.h"

static int	max_bits(int size)
{
	int	bits;
	int	max;

	max = size -1;
	bits = 0;

	while ((max >> bits) != 0)
		bits++;
	return (bits);
}

static void	radix_onepass(t_ps *ps, int bit)
{
	int	i;
	int	size;

	size = ps->a.size;
	i = 0;
	while (i < size)
	{
		if ((ps->a.top->index >> bit) & 1)
			ra(ps);
		else
			pb(ps);
		i++;
	}
	while (ps->b.size > 0)
		pa(ps);
}

void	sort_complex(t_ps *ps)
{
	int	bit;
	int	bits;
 
	if (!ps || ps->a.size <= 1)
		return ;
	if (ps->a.size <= 5)
	{
		sort_small(ps, ps->a.size);
		return ;
	}
	bits = max_bits(ps->a.size);
	bit = 0;
	while (bit < bits)
	{
		radix_onepass(ps, bit);
		bit++;
	}
}
