#include "push_swap.h"
#include <stdio.h>

static void	add_element_to_sorted_stack(t_stack *stack_a, t_stack *stack_b, t_data *data)
{
	int	i;
	char	*cmd_mv;
	char	*cmd_ret;

	cmd_mv = "rb";
	cmd_ret = "rrb";
	i = 0;
	while (i < stack_b->size)
	{
		if (stack_a->array[index_pos(stack_a, 0)] > stack_b->array[index_pos(stack_b, i)])
			break ;
		i++;
	}
	if (i < stack_b->size / 2)
	{
		cmd_mv = "rrb";
		cmd_ret = "rb";
	}	
	cmd_loop(data, cmd_mv, i);
	push(stack_b, stack_a);
	ft_putstr_fd("pb\n", STDOUT_FILENO);
	cmd_loop(data, cmd_ret, i);
}

void	insertion_sort(t_data *data)
{
	t_stack *stack_a;
	t_stack *stack_b;
	int	i;

	stack_a = data->stack_a;
	stack_b = data->stack_b;
	i = 0;
	while (i < stack_a->size)
	{
		if (stack_a->array[index_pos(stack_a, i)] > stack_a->array[index_pos(stack_a, i + 1)])
		{
			if (i > 0)
			{
				cmd_loop(data, "pb", i);
				swap(stack_a);
				ft_putstr_fd("sa\n", STDOUT_FILENO);
				add_element_to_sorted_stack(stack_a, stack_b, data);
				cmd_loop(data, "pa", i + 1);
			}
			else
			{
				swap(stack_a);
				ft_putstr_fd("sa\n", STDOUT_FILENO);
			}
		}
		i++;
	}
}
