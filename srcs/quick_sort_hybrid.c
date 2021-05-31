#include "push_swap.h"

static double	choose_pivot(t_stack stack, int recorrido)
{
	double	median;
	int		i;

	median = 0;
	i = 0;
	while (i < recorrido)
	{
		median += stack_ud(stack, i);
		i++;
	}
	median /= (double)recorrido;
	return (median);
}

static int	push_next_pos(int recorrido, t_stack stack, double pivot)
{
	int	pos;

	pos = 0;
	while (pos < recorrido)
	{
		if ((double)stack_ud(stack, pos) < pivot)
			return (pos);
		pos++;
	}
	return (-1);
}

static int	partition(int recorrido, t_data *data)
{
	int		i;
	int		pos;
	int		rot_n;
	int		first_step;
	double	pivot;

	i = 0;
	rot_n = 0;
	pivot = choose_pivot(data->stack[S_A], recorrido);
	first_step = 1 * (recorrido == data->stack[S_A].size);
	while (i < recorrido)
	{
		pos = push_next_pos(recorrido - i, data->stack[S_A], pivot);
		if (pos == -1)
			break ;
		rot_n += pos;
		i += pos + 1;
		exec_instr_loop(ROT_ID, S_A, pos, data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
	}
	exec_instr_loop(RROT_ID, S_A, rot_n * (!first_step), data);
	return (data->stack[S_B].size + 1 * (data->stack[S_B].size == 0));
}

static int	find_biggest(t_stack stack)
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_ud(stack, 0);
	while (i < stack.size)
	{
		if (stack_ud(stack, i) > biggest)
		{
			biggest = stack_ud(stack, i);
			biggest_pos = i;
		}
		i++;
	}
	return (biggest_pos);
}

static void	selection_sort_subarray(t_data *data)
{
	int		pos;
	t_stack	stack;

	stack = data->stack[S_B];
	if (stack.size == 0)
		return ;
	if (stack.size == 2)
	{
		if (stack_ud(stack, 0) < stack_ud(stack, 1))
			exec_instr_loop(SWAP_ID, S_B, 1, data);
		exec_instr_loop(PUSH_ID, S_A, 2, data);
		return ;
	}
	pos = find_biggest(data->stack[S_B]);
	if (pos < stack.size / 2)
		exec_instr_loop(ROT_ID, S_B, pos, data);
	else
		exec_instr_loop(RROT_ID, S_B, stack.size - pos, data);
	exec_instr_loop(PUSH_ID, S_A, 1, data);
	selection_sort_subarray(data);
}

static void	quick_sort(int recorrido, t_data *data)
{	
	int	n;

	if (check_already_sorted(data->stack[S_A], recorrido))
	{
		exec_instr_loop(ROT_ID, S_A, recorrido, data);
		return ;
	}
	n = partition(recorrido, data);
	if (data->stack[S_B].size <= 40)
	{
		n = data->stack[S_B].size;
		selection_sort_subarray(data);
	}
	else
		exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
	quick_sort(n, data);
	quick_sort(recorrido - n, data);
}

void	quick_sort_init(t_data *data)
{
	if (check_already_sorted(data->stack[S_A], data->stack[S_A].size))
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (data->stack[S_A].size < 2000)
		selection_sort(data);
	else
		quick_sort(data->stack[S_A].size, data);
}
