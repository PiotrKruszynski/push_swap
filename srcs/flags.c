#include "push_swap.h"

void	set_strategy(t_ps *ps, t_strategy s)
{
	if (ps->strategy != NO_STRATEGY)
		ps_error(ps);
	ps->strategy = s;
}

void	set_flag(t_ps *ps, char *arg)
{
	if (!ft_strncmp(arg, "--simple", 9))
		set_strategy(ps, SIMPLE);
	else if (!ft_strncmp(arg, "--medium", 9))
		set_strategy(ps, MEDIUM);
	else if (!ft_strncmp(arg, "--complex", 10))
		set_strategy(ps, COMPLEX);
	else if (!ft_strncmp(arg, "--adaptive", 11))
		set_strategy(ps, ADAPTIVE);
	else if (!ft_strncmp(arg, "--bench", 8))
		ps->bench_mode = 1;
	else
		ps_error(ps);
}