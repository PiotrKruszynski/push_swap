#include "push_swap.h"

void	ps_error(t_ps *ps)
{
	stack_free(&ps->a);
	stack_free(&ps->b);
	write(2, "Error\n", 6);
	exit(1);
}

static int	is_valid_int(char *str)
{
	int		i;
	long	value;
	int		sign;

	if (!str || !*str || !str[i])
		return (0);
	i = 0;
	sign = 1;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	
	value = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		value = value * 10 +(str[i] - '0');
		if (value *sign > INT_MAX || value * sign < INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

void	parse_args(t_ps *ps, int argc, char **argv)
{
	int		i;
	t_node	*node;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_int(argv[i]))
			ps_error(ps);
		node = node_new(ft_atoi(argv[i]));
		if (!node)
			ps_error(ps);
		stack_add_back(&ps->a, node);
		i++;
	}
}