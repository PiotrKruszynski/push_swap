#include "push_swap.h"

static void	debug_print(t_stack *stack)
{
	t_node	*curr;

	curr = stack->top;
	while (curr != NULL)
	{
		ft_putnbr_fd(curr->value, 1);
		write(1, "\n", 1);
		curr = curr->next;
	}
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	stack_init(&ps.a);
	stack_init(&ps.b);
	parse_args(&ps, argc, argv);
	debug_print(&ps.a);
	ra(&ps);
	debug_print(&ps.a);
	stack_free(&ps.a);
	stack_free(&ps.b);
	return (0);
}

