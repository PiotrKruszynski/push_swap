#include "push_swap.h"

static void	print_disorder(double disorder)
{
	int	scaled;

	scaled = (int)(disorder * 10000.0);
	ft_putstr_fd("[bench] disorder:  ", 2);
	ft_putnbr_fd((scaled / 100), 2);
	ft_putchar_fd('.', 2);
	if ((scaled % 100) < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd((scaled % 100), 2);
	ft_putchar_fd('%', 2);
	ft_putchar_fd('\n', 2);
}

static void	print_strategy(t_ps *ps)
{
	ft_putstr_fd("[bench] strategy:  ", 2);
	if (ps->strategy == SIMPLE)
		ft_putstr_fd("Simple / O(n²)\n", 2);
	else if (ps->strategy == MEDIUM)
		ft_putstr_fd("Medium / O(n√n))\n", 2);
	else if (ps->strategy == COMPLEX)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (ps->disorder < 0.2)
		ft_putstr_fd("Adaptive / O(n²)\n", 2);
	else if (ps->disorder < 0.5)
		ft_putstr_fd("Adaptive / O(n√n)\n", 2);
	else
		ft_putstr_fd("Adaptive / O(n log n)\n", 2);
}

static void	print_connector(char *name, int count, char *sep)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(count, 2);
	ft_putstr_fd(sep, 2);
}

static void	print_counts(t_ps *ps)
{
	ft_putstr_fd("[bench] ", 2);
	print_connector("sa", ps->op_counter[O_SA], "  ");
	print_connector("sb", ps->op_counter[O_SB], "  ");
	print_connector("ss", ps->op_counter[O_SS], "  ");
	print_connector("pa", ps->op_counter[O_PA], "  ");
	print_connector("pb", ps->op_counter[O_PB], "\n");
	ft_putstr_fd("[bench] ", 2);
	print_connector("ra", ps->op_counter[O_RA], "  ");
	print_connector("rb", ps->op_counter[O_RB], "  ");
	print_connector("rr", ps->op_counter[O_RR], "  ");
	print_connector("rra", ps->op_counter[O_RRA], "  ");
	print_connector("rrb", ps->op_counter[O_RRB], "  ");
	print_connector("rrr", ps->op_counter[O_RRR], "\n");
}

void	print_bench(t_ps *ps)
{
	if (!ps || !ps->bench_mode)
		return ;
	print_disorder(ps->disorder);
	print_strategy(ps);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(ps->total_ops, 2);
	ft_putstr_fd("\n", 2);
	print_counts(ps);
}