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
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
// 	v2
// int	is_number(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str || str[0] == '\0')
// 		return (0);
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	if (str[i] == '\0')
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

//	v3 ---------- poprawna?
// int	is_number(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str || str[i] == '\0')
// 		return (0);
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	if (str[i] == '\0')
// 		return (0);
// 	while (str[i])
// 	{
// 		if (str[i] < '0' || str[i] > '9')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


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
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if ((sign == 1 && num > 2147483647) || (sign == -1 && (-num) < -2147483648))
			return (0);
		i++;
	}
	*result = num * sign;
	return (1);
}
// dodac obsluge formatu "1 2 3"
void	parse_args(t_ps *ps, int argc, char **argv)
{
	int			i;
	long long	value;
	t_node		*node;

	stack_init(&ps->a);
	stack_init(&ps->b);
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
			ps_error(ps);
		if (!ft_atoi_overflow(argv[i], &value))
			ps_error(ps);
		if (duplicate(&ps->a, (int)value))
			ps_error(ps);
		node = node_new((int)value);
		if (!node)
			ps_error(ps);
		stack_add_back(&ps->a, node);
		i++;
	}
}

// void	parse_args(t_ps *ps, int argc, char **argv)
// {
// 	int	i;
// 	t_node	*node;

// 	ps->a = NULL;
// 	ps->b = NULL;
// 	i = 1;
// 	while (i < argc)
// 	{
// 		node = node_new(ft_atoi_overflow(argv[i]));
// 		if (!node)
// 			ps_error(ps);
// 		stackadd_back(&ps->a, node);
// 		i++;
// 	}
// }