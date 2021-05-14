#include "push_swap.h"

static int	index_pos(t_stack *stack_s, int pos)
{
	return (stack_s->size - 1 - pos);
}

static void	cmd_loop(t_data *data, char *cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmp_instr_list(cmd, data);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		i++;
	}
}

static void	add_element_to_sorted_stack(t_stack *stack_a, t_stack *stack_b, t_data *data)
{
	int	i;
	char	*cmd_mv;
	char	*cmd_ret;

	cmd_mv = "rb\n";
	cmd_ret = "rrb\n";
	if (i < stack_b->size / 2) // comprobar esto
	{
		cmd_mv = "rrb\n";
		cmd_ret = "rb\n";
	}
	i = 0;
	while ((i + 1) < stack_b->size)
	{
		if (stack_a->array[index_pos(stack_a, 0)] < stack_b->array[index_pos(stack_b, i)])
			break ;
		i++;
	}
	// si el elemento a pushear es mas grande que el primero de la lista ordenada, saltamos esta parte (no push)
	cmd_loop(data, "rb\n", i);
	push(stack_b, stack_a);
	ft_putstr_fd("pb\n", STDOUT_FILENO);
	cmd_loop(data, "rrb\n", i);
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
			//push_to_stack_b();
				cmd_loop(data, "pb\n", i);
				swap(stack_a);
			//swap_in_a();
				ft_putstr_fd("sa\n", STDOUT_FILENO);
			//find_position_in_sorted_stack();
			//setup_sorted_stack();
			//push_to_stack_b();
			//reorder_sorted_stack();
				add_element_to_sorted_stack(stack_a, stack_b, data);
			//push_to_stack_a();
				cmd_loop(data, "pa\n", i + 1); // ??
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
