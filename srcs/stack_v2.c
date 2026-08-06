#include "push_swap.h"

void	stack_add_front(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->size == 0)
	{
		stack->top = new_node;
		stack->bottom = new_node;
		new_node->next = NULL;
		new_node->prev = NULL;
	}
	else
	{
		new_node->next = stack->top;
		new_node->prev = NULL;
		stack->top->prev = new_node;
		stack->top = new_node;
	}
	stack->size++;
}

void	stack_add_back(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	new_node->next = NULL;
	if (stack->size == 0)
	{
		stack->top = new_node;
		stack->bottom = new_node;
	}
	else
	{
		new_node->prev = stack->bottom;
		stack->bottom->next = new_node;
		stack->bottom = new_node;
	}
	stack->size++;
}

t_node	*stack_pop(t_stack *stack)
{
	t_node	*popped_node;

	if (!stack || stack->size == 0)
		return (NULL);
	popped_node = stack->top;
	stack->top = stack->top->next;
	if (stack->top)
		stack->top->prev = NULL;
	else
		stack->bottom = NULL;
	popped_node->next = NULL;
	popped_node->prev = NULL;
	stack->size--;
	return (popped_node);
}
