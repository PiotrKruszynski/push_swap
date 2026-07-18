#include "push_swap.h"

static void	debug_print(t_node *stack)
{
	while (stack)
	{
		ft_putnbr_fd(stack->value, 1);
		write(1, "\n", 1);
		stack = stack->next;
	}
}

int	main(int argc, char **argv)
{
	t_ps	ps; // dostaje dwa wskazniki ze smieciami

	if (argc < 2)
		return (0);
	parse_args(&ps, argc, argv);
	debug_print(ps.a);
	stack_free(&ps.a);
	stack_free(&ps.b);
	return (0);

/*
	i = 1;
	strategy = ADAPTIVE;
	bench = false;

	while (argv[i] == "--")
		rozpoznaje flage 
		ustawiam strategy
		ustawiam bench
		nieznana flaga - error 
		i++;
*/
}

