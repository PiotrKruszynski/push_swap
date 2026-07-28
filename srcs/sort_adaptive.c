#include "push_swap.h"

void	sort_adaptive(t_ps *ps)
{
	if (!ps || ps->a.size <= 1)
		return ;
	if (ps->a.size <= 5)
		sort_small(ps, ps->a.size);
	else if (ps->disorder < 0.2)
		sort_simple(ps);
	else if (ps->disorder < 0.5)
		sort_medium(ps);
	else
		sort_complex(ps);
}
