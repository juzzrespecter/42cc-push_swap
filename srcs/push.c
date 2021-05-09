#include "push_swap.h"

void	push(t_stack *stack_push, t_stack *stack_pop)
{
	int	size_push;
	int	size_pop;

	size_push = stack_push->size;
	size_pop = stack_pop->size;
	if (size_push == 0)
		return ;
	stack_pop->size++;
	stack_pop->stack[size_pop] = stack_push->stack[size_push - 1];
	stack_push->stack[size_push - 1] = 0;
	stack_push->size--;
}
