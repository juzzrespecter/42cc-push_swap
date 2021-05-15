#include "push_swap.h"

int		find_smaller_pos(t_stack *stack_s, int i)
{
	int	count;
	int	n_to_compare;
	int	pos;
	int	*arr;

	pos = 0;
	count = 0;
	arr = stack_s->array;
	n_to_compare = arr[index_pos(stack_s, 0)];
	while (pos < stack_s->size - i)
	{
		if (n_to_compare > arr[index_pos(stack_s, pos)])
		{
			count = pos;
			n_to_compare = arr[index_pos(stack_s, pos)];
		}
		pos++;
	}
	return (count);
}

void	selection_sort(t_data *data)
{
	int	i;
	int	pos;

	i = 0;
	// check si ya esta ordenada
	
	while (i < data->stack_a->size)
	{
			pos = find_smaller_pos(data->stack_a, i);
			cmd_loop(data, "pb", pos);
			rotate(data->stack_a);
			ft_putstr_fd("ra\n", STDOUT_FILENO);
			cmd_loop(data, "pa", pos);
		i++;
	}
}
