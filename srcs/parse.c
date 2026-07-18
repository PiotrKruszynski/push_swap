#include "push_swap.h"

void	ps_error(t_ps *ps)
{
	stack_free(&ps->a);
	stack_free(&ps->b);
	write(2, "Error\n", 6);
	exit(1);
}

void	parse_args(t_ps *ps, int argc, char **argv)
{
	int	i;
	t_node	*node;

	ps->a = NULL;
	ps->b = NULL;
	i = 1;
	while (i < argc)
	{
		node = node_new(ft_atoi(argv[i]));
		if (!node)
			ps_error(ps);
		stackadd_back(&ps->a, node);
		i++;
	}
}