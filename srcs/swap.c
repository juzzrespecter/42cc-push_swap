#include "push_swap.h"

void	swap(t_stack *stack_s)
{
	int	aux;

	if (stack_s->size < 2)
		return ;
	aux = stack_s->array[stack_s->size - 1];
	stack_s->array[stack_s->size - 1] = stack_s->array[stack_s->size - 2];
	stack_s->array[stack_s->size - 2] = aux;
}

void	swap_both(t_stack *stack_a, t_stack *stack_b)
{
	swap(stack_a);
	swap(stack_b);
}
