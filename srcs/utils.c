#include "push_swap.h"

/* dodatkowe funkcje */
int is_sorted(t_stack *stack)
{
    t_node  *curr;

    if (!stack || stack->size < 2)
        return (1);
    curr = stack->top;
    while (curr->next)
    {
        if (curr->value > curr->next->value)
            return (0);
        curr = curr->next;
    }
    return (1);
}
/*
void	run_strategy(t_ps *ps) // mogę tez z swich i break
{
	if (ps->strategy == SIMPLE)
		sort_simple(ps);
	else if (ps->strategy == MEDIUM)
		sort_medium(ps);
	else if (ps->strategy == COMPLEX)
		sort_complex(ps);
	else
		sort_adaptive(ps);
} */