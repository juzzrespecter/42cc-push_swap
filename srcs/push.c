#include "push_swap.h"

void	push(t_data *data, int stack_id)
{
	t_stack *stack_push;
	t_stack	*stack_pop;
	int	size_pop;
	int	size_push;
	
	stack_push = &data->stack[stack_id];
	stack_pop = &data->stack[1 * (stack_id == 0)];
	size_pop = stack_pop->size;
	size_push = stack_push->size;
	if (size_pop == 0)
		return ;
	stack_push->size++;
	stack_push->array[size_push] = stack_pop->array[size_pop - 1];
	stack_pop->array[size_pop - 1] = 0;
	stack_pop->size--;
}
