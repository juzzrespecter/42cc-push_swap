#include "push_swap.h"

void	rotate(t_stack *stack_s)
{
	int	size;
	int	aux;
	int	i;

	size = stack_s->size;
	if (size < 2)
		return ;
	aux = stack_s->stack[size - 1];
	i = 0;
	while (i < size - 1)
	{
		stack_s->stack[size - i - 1] = stack_s->stack[size - i - 2];
		i++;
	}
	stack_s->stack[0] = aux;
}

void	rotate_both(t_stack *stack_a, t_stack *stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
}

void	rev_rotate(t_stack *stack_s)
{
	int	size;
	int	aux;
	int	i;

	size = stack_s->size;
	if (size < 2)
		return ;
	aux = stack_s->stack[0];
	i = 0;
	while (i < size - 1)
	{
		stack_s->stack[i] = stack_s->stack[i + 1];
		i++;
	}
	stack_s->stack[size - 1] = aux;
}

void	rev_rotate_both(t_stack *stack_a, t_stack *stack_b)
{
	rev_rotate(stack_a);
	rev_rotate(stack_b);
}
