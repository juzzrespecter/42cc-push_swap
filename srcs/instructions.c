#include "push_swap.h"

void	push(int stack_id, t_data *data)
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

void	swap(int stack_id, t_data *data)
{
	t_stack *stack_s;
	int	aux;

	stack_s = &data->stack[stack_id - 2 * (stack_id == 2)];
	if (stack_s->size < 2)
		return ;
	aux = stack_s->array[stack_s->size - 1];
	stack_s->array[stack_s->size - 1] = stack_s->array[stack_s->size - 2];
	stack_s->array[stack_s->size - 2] = aux;
	if (stack_id == 2)
		swap(S_B, data);
}

void	rotate(int stack_id, t_data *data)
{
	t_stack	*stack_s;
	int	size;
	int	aux;
	int	i;

	stack_s = &data->stack[stack_id - 2 * (stack_id == 2)];
	size = stack_s->size;
	if (size < 2)
		return ;
	aux = stack_s->array[size - 1];
	i = 0;
	while (i < size - 1)
	{
		stack_s->array[size - i - 1] = stack_s->array[size - i - 2];
		i++;
	}
	stack_s->array[0] = aux;
	if (stack_id == 2)
		rotate(S_B, data);
}

void	rev_rotate(int stack_id, t_data *data)
{
	t_stack	*stack_s;
	int	size;
	int	aux;
	int	i;

	stack_s = &data->stack[stack_id - 2 * (stack_id == 2)];
	size = stack_s->size;
	if (size < 2)
		return ;
	aux = stack_s->array[0];
	i = 0;
	while (i < size - 1)
	{
		stack_s->array[i] = stack_s->array[i + 1];
		i++;
	}
	stack_s->array[size - 1] = aux;
	if (stack_id == 2)
		rev_rotate(S_B, data);
}
