#include "push_swap.h"
/*
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
} */

static void	init_ps(t_ps *ps)
{
	stack_init(&ps->a);
	stack_init(&ps->b);
	ps->strategy = NO_STRATEGY;
	ps->disorder = 0.0;
	ps->total_ops = 0;
	ps->bench_mode = 0;
	ft_bzero(ps->op_counter, sizeof(ps->op_counter));
}

void	run_strategy(t_ps *ps)
{
	if (ps->strategy == SIMPLE)
		sort_simple(ps);
	else if (ps->strategy == MEDIUM)
		sort_medium(ps);
	else if (ps->strategy == COMPLEX)
		sort_complex(ps);
	else
		sort_adaptive(ps);
}

int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	init_ps(&ps);
	parse_args(&ps, argc, argv);
	indexing_stack(&ps);
	ps.disorder = compute_disorder(&ps.a);
	// ft_putnbr_fd(compute_disorder(&ps.a), 1);
	// debug_print(&ps.a);
	if (!is_sorted(&ps.a))
		run_strategy(&ps);
	// debug_print(&ps.a);
	// ft_putnbr_fd(compute_disorder(&ps.a), 1);
	// write(1, "\n", 1);
	print_bench(&ps);
	stack_free(&ps.a);
	stack_free(&ps.b);
	return (0);
}
