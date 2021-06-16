#include "push_swap.h"

int	check_if_sorted(t_stack stack, int pass)
{
	int	i;

	i = 0;
	while ((i + 1) < pass)
	{
		if (stack_ud(stack, i) > stack_ud(stack, i + 1))
			return (0);
		i++;
	}
	return (1);
}

int	next_upper_half(int pivot_min, int pivot_max, t_stack stack)
{
	int	index;
	int	n;

	index = 0;
	if (stack.size == 1)
	{
		n = stack_ud(stack, 0);
		if (n >= pivot_min && n <= pivot_max)
			return (0);
		return (-1);
	}
	while (index < stack.size / 2)
	{
		n = stack_ud(stack, index);
		if (n >= pivot_min && n <= pivot_max)
			return (index);
		index++;
	}
	return (-1);
}

int	next_lower_half(int pivot_min, int pivot_max, t_stack stack)
{
	int	index;
	int	n;

	index = 0;
	if (stack.size == 1)
	{
		n = stack_ud(stack, 0);
		if (n >= pivot_min && n <= pivot_max)
			return (1);
		return (-1);
	}
	while (index < stack.size / 2)
	{
		n = stack_ud(stack, stack.size - (index + 1));
		if (n >= pivot_min && n <= pivot_max)
			return (index + 1);
		index++;
	}
	return (-1);
}

int	next_catcher(int n_to_push, int id, t_data *data)
{
	int	n_stack;
	int	i;

	i = 0;
	if (data->stack[!id].size == 0)
		return (0);
	n_stack = stack_ud(data->stack[!id], i);
	while (i < data->stack[!id].size && n_stack > n_to_push && id == STACK_ID_A)
	{
		i++;
		if (i < data->stack[!id].size)
			n_stack = stack_ud(data->stack[!id], i);
	}
	while (i < data->stack[!id].size && n_stack < n_to_push && id == STACK_ID_B)
	{
		i++;
		if (i < data->stack[!id].size)
			n_stack = stack_ud(data->stack[!id], i);
	}
	return (i);
}

void	sort_three(t_data *data, t_stack stack)
{
	int	**index_table;
	int	rot_position;

	index_table = get_index_table(stack.array, stack.size);
	if (stack.size == 3)
	{
		rot_position = index_table[2][1];
		if (rot_position != 2)
			exec_instr_loop(ROT_ID + (rot_position == 1), STACK_ID_A, 1, data);
	}
	if (stack_ud(stack, 0) > stack_ud(stack, 1))
		exec_instr_loop(SWAP_ID, STACK_ID_A, 1, data);
	free_table(index_table, stack.size);
}
