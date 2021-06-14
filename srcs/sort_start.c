#include "push_swap.h"

static void	init_pivot_a(t_stack stack, int *pivot_a, int n_steps)
{
	int	i;
	int	**index_table;

	i = 0;
	index_table = get_index_table(stack.array, stack.size);
	while (i < n_steps + 1)
	{
		pivot_a[i] = index_table[i  * ((stack.size / n_steps) - 1)][0];
		i++;
	}
	free_table(index_table, stack.size);
}

static int	next_upper_half(int pivot_min, int pivot_max, t_stack stack)
{
	int	index;
	int	n;

	index = 0;
	while (index < stack.size / 2)
	{
		n = stack_ud(stack, index);
		if (n >= pivot_min && n <= pivot_max)
			return (index);
		index++;
	}
	return (-1);
}

static int	next_lower_half(int pivot_min, int pivot_max, t_stack stack)
{
	int	index;
	int	n;

	index = 0;
	while (index < stack.size / 2)
	{
		n = stack_ud(stack, stack.size - (index + 1));
		if (n >= pivot_min && n <= pivot_max)
			return (index + 1);
		index++;
	}
	return (-1);
}

static int	**selection_sort_prev_table(int pivot_a[3], t_data *data)
{
	int	**next_table;
	int	index;

	index = 0;
	next_table = (int **)malloc(sizeof(int *) * 3);
	while (index < 4)
	{
		next_table[index] = (int *)malloc(sizeof(int) * 3);
		ft_bzero(next_table[index], sizeof(int) * 3);
		if (!(index % 2))
			next_table[index][0] = next_upper_half(pivot_a[0 + (index > 1)], \
					pivot_a[1 + (index > 1)], data->stack[STACK_ID_A]);
		if (index % 2)
		{
			next_table[index][0] = next_lower_half(pivot_a[0 + (index > 1)], \
					pivot_a[1 + (index > 1)], data->stack[STACK_ID_A]);
			next_table[index][1] = 1;
		}
		next_table[index][0] += 1 * (pos_array[index][0] != -1) * !(index > 1);
		next_table[index][2] = !(index > 1);
	}
	return (next_table);
}

static void	selection_sort_prev_step(int pivot_a[3], t_data *data)
{
	int	**next_table;
	int	index;

	while (1)
	{
//		pos_array = (int **)malloc(sizeof(int *) * 4);
//		index = 0;
/*		while (index < 4)
		{
			pos_array[index] = (int *)malloc(sizeof(int) * 3);
			ft_bzero(pos_array[index], sizeof(int) * 3);
			if (!(index % 2))
				pos_array[index][0] = next_upper_half(pivot_a[0 + (index > 1)], \
						pivot_a[1 + (index > 1)], data->stack[STACK_ID_A]);
			if (index % 2)
			{
				pos_array[index][0] = next_lower_half(pivot_a[0 + (index > 1)],\
						pivot_a[1 + (index > 1)], data->stack[STACK_ID_A]);
				pos_array[index][1] = 1;
			}
			pos_array[index][0] += 1 * (pos_array[index][0] != -1) * !(index > 1);
			pos_array[index][2] = !(index > 1);
			index++;
		}
*/
		index = 0;
		next_table = selection_sort_prev_table(pivot_a, data);
		heap_sort(next_table, 4);
		while (index < 4 && next_table[index][0] == -1)
			index++;
		if (index == 4 && next_table[index - 1][0] == -1)
			break ;
		index = (index > 3) ? 3 : index; // ??
		exec_instr_loop(ROT_ID + (next_table[index][1] == 1), STACK_ID_A, \
				next_table[index][0] - (next_table[index][2] == 1), data);
		exec_instr_loop(PUSH_ID, STACK_ID_B, 1, data);
		if (next_table[index][2] == 1)
			exec_instr_loop(ROT_ID, STACK_ID_B, 1, data);
		free_table(next_table, 4);
	}
	free_table(next_table, 4);
}

void	sort_start(t_data *data)
{
	int pivot_a[data->n_steps + 1];
	int	pivot_a_step[3];
	int	index;

	if (check_if_sorted(data->stack[STACK_ID_A], data->stack[STACK_ID_A].size))
		return ;
	if (data->stack[STACK_ID_A].size < SMALL_LIMIT)
	{
		data->n_ins = 1; // tmp
		selection_sort(data, STACK_ID_A);
		exec_instr_loop(PUSH_ID, STACK_ID_A, data->stack[STACK_ID_B].size, data);
		return ;
	}
	init_pivot_a(data->stack[STACK_ID_A], pivot_a, data->n_steps);
	ft_bzero(pivot_a_step, sizeof(int) * 3);
	index = 0;
	while (index < data->n_steps / 2 ) // check last iteration !!!!!!!!!!!!!!!!!
	{
		pivot_a_step[0] = pivot_a[(data->n_steps / 2) - (index + 1)];
		pivot_a_step[1] = pivot_a[data->n_steps / 2];
		pivot_a_step[2] = pivot_a[(data->n_steps / 2) + (index + 1)];
		selection_sort_prev_step(pivot_a_step, data);
		index++;
	}
	exec_instr_loop(PUSH_ID, STACK_ID_B, data->stack[STACK_ID_A].size, data);  // check this
	selection_sort(data, STACK_ID_B);
}
