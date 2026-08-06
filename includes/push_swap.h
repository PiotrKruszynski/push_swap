/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwlodars <kwlodars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 11:54:30 by kwlodars          #+#    #+#             */
/*   Updated: 2026/08/06 11:54:34 by kwlodars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include <limits.h>
# include <stdio.h>

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE,
	NO_STRATEGY
}	t_strategy;

typedef enum e_op_count
{
	O_SA,
	O_SB,
	O_SS,
	O_PA,
	O_PB,
	O_RA,
	O_RB,
	O_RR,
	O_RRA,
	O_RRB,
	O_RRR,
	OP_COUNT
}	t_op_count;

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
	double			disorder;
	int				bench_mode;
	int				total_ops;
	int				op_counter[OP_COUNT];
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
void	indexing_stack(t_ps *ps);
int		find_min_position(t_stack *stack, int size);

// sort_*.c
void	sort_simple(t_ps *ps);
void	sort_medium(t_ps *ps);
void	sort_complex(t_ps *ps);
void	sort_adaptive(t_ps *ps);

// sort_small.c
void	sort_three(t_ps *ps);
void	push_min_to_b(t_ps *ps, int min_pos, int size);
void	sort_small(t_ps *ps, int size);

// disorder.c + bench.c
double	compute_disorder(t_stack *stack);
void	print_bench(t_ps *ps);

//flags.c
void	set_strategy(t_ps *ps, t_strategy s);
void	set_flag(t_ps *ps, char *arg);

//sort_medium_v1_v2
int		get_cost(int pos, int size);
void	rotate_b_to_top(t_ps *ps, int pos);
int		find_pos_b(t_stack *stack, int target_index);
void	cheap_push_back(t_ps *ps, int pos_max, int pos_next, int *target_max);
int		get_chunk_size(int size);
void	push_back_to_a(t_ps *ps);
void	push_to_b(t_ps *ps, int min_chunk, int max_chunk);
void	divide_chunks(t_ps *ps);
void	sort_medium(t_ps *ps);
#endif