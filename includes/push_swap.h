#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
#include <limits.h>

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strategy;

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
}	t_stack;

typedef struct s_ps
{
	t_stack			a;
	t_stack			b;
	t_strategy		strategy;
}	t_ps;

// parse.c
void	ps_error(t_ps *ps);
int		is_number(char *str);
int		duplicate(t_stack *stack, int value);
int		ft_atoi_overflow(char *str, long long *result);
void	parse_args(t_ps *ps, int argc, char **argv);


//stack.c
t_node	*node_new(int value);
void	stack_init(t_stack *stack);
void	stack_add_back(t_stack *stack, t_node *new_node);
void	stack_add_front(t_stack *stack, t_node *new_node);
t_node	*stack_pop(t_stack *stack);
void	stack_free(t_stack *stack);

//ops_*.c

void	sa(t_ps *ps);
void	sb(t_ps *ps);
void	ss(t_ps *ps);

void	pa(t_ps *ps);
void	pb(t_ps *ps);

void	ra(t_ps *ps);
void	rb(t_ps *ps);
void	rr(t_ps *ps);

void	rra(t_ps *ps);
void	rrb(t_ps *ps);
void	rrr(t_ps *ps);
// utils.c
int		is_sorted(t_stack *stack);

// sort_*.c
void	sort_simple(t_ps *ps);
#endif