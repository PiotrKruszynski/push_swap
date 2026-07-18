#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_node
{
	int				value;
	struct s_node	*next;
	struct s_node	*head;
}	t_node;

typedef struct s_ps
{
	t_node	*a; // wskaznik na gore stosu a
	t_node	*b; // wskaznik na gore stosu b
	
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