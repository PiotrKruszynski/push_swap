#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

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
	t_stack	a;
	t_stack	b;
}	t_ps;

// parse.c
void	parse_args(t_ps *ps, int argc, char **argv);
void	ps_error(t_ps *ps);

// stack.c
t_node	*node_new(int value);
void	stackadd_back(t_node **stack, t_node *node);
void	stack_free(t_node **stack);
int		stack_size(t_node *stack);

#endif