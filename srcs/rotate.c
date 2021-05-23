#include "push_swap.h"

void	rotate(t_data *data, int stack_id)
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
		rotate(data, S_B);
}

void	rev_rotate(t_data *data, int stack_id)
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
		rev_rotate(data, S_B);
}
