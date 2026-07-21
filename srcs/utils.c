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