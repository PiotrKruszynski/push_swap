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

static void	init_ps(t_ps *ps)
{
	stack_init(&ps->a);
	stack_init(&ps->b);
	ps->strategy = ADAPTIVE;
}

// run_strategy if ps->strategy == SIMPLE sort_simple(ps)

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	init_ps(&ps);
	parse_args(&ps, argc, argv);
	debug_print(&ps.a);
	if (!is_sorted(&ps.a))
		ra(&ps);
	debug_print(&ps.a);
	stack_free(&ps.a);
	stack_free(&ps.b);
	return (0);
}

