#include "push_swap.h"

void	ps_error(t_ps *ps)
{
	stack_free(&ps->a);
	stack_free(&ps->b);
	write(2, "Error\n", 6);
	exit(1);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	duplicate(t_stack *stack, int value)
{
	t_node	*current;

	if (!stack)
		return (0);
	current = stack->top;
	while (current != NULL)
	{
		if (current->value == value)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_atoi_overflow(char *str, long long *result)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (ft_strlen(&str[i]) > 11)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= sign;
	if (num > INT_MAX || num < INT_MIN)
		return (0);
	*result = num;
	return (1);
}

static int	set_flag(t_ps *ps, char *arg)
{
	if (!ft_strncmp(arg, "--simple", 9))
		ps->strategy = SIMPLE;
	else if (!ft_strncmp(arg, "--medium", 9))
		ps->strategy = MEDIUM;
	else if (!ft_strncmp(arg, "--complex", 10))
		ps->strategy = COMPLEX;
	else if (!ft_strncmp(arg, "--adaptive", 11))
		ps->strategy = ADAPTIVE;
	else if (!ft_strncmp(arg, "--bench", 8))
		ps->bench_mode = 1;
	else
		return (0);
	return (1);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
static void	add_num(t_ps *ps, char *str, char **split)
{
	long long	val;
	t_node		*node;

	val = 0;

	if (!is_number(str) || !ft_atoi_overflow(str, &val)
		|| duplicate(&ps->a, (int)val))
	{
		free_split(split);
		ps_error(ps);
	}
	node = node_new((int)val);
	if (!node)
	{
		free_split(split);
		ps_error(ps);
	}
	stack_add_back(&ps->a, node);
}

void	parse_args(t_ps *ps, int argc, char **argv)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
		{
			if (!set_flag(ps, argv[i]))
				ps_error(ps);
		}
		else
		{
			split = ft_split(argv[i], ' ');
			if (!split)
				ps_error(ps);
			if (!split[0])
			{
				free_split(split);
				ps_error(ps);
			}
			j = -1;
			while (split[++j])
				add_num(ps, split[j], split);
			free_split(split);
		}
	}
}



// void	parse_args(t_ps *ps, int argc, char **argv)
// {
// 	int			i;
// 	long long	value;
// 	t_node		*node;

// 	i = 1;
// 	while (i < argc && argv[i][0] == '-' && argv[i][1] == '-')
// 	{
// 		set_flag(ps, argv[i]);
// 		i++;
// 	}
// 	while (i < argc)
// 	{
// 		if (!is_number(argv[i]))
// 			ps_error(ps);
// 		if (!ft_atoi_overflow(argv[i], &value))
// 			ps_error(ps);
// 		if (duplicate(&ps->a, (int)value))
// 			ps_error(ps);
// 		node = node_new((int)value);
// 		if (!node)
// 			ps_error(ps);
// 		stack_add_back(&ps->a, node);
// 		i++;
// 	}
// }

