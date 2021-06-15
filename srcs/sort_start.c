#include "push_swap.h"

static int	*pivot_get(t_stack stack, int n_steps)
{
	int	i;
	int	i_table;
	int	*pivot;
	int	**index_table;

	i = 0;
	pivot = (int *)malloc(sizeof(int) * (n_steps + 1));
	index_table = get_index_table(stack.array, stack.size);
	while (i < (n_steps + 1))
	{
		i_table = i * (stack.size / n_steps);
		if (i == 0)
			i_table = 0;
		pivot[i] = index_table[i_table - (i_table == stack.size)][0];
		i++;
	}
	free_table(index_table, stack.size);
	return (pivot);
}

static int	**selection_sort_prev_table(int pivot[3], t_data *data)
{
	int	**next_table;
	int	index;

	next_table = (int **)malloc(sizeof(int *) * 4);
	index = 0;
	while (index < 4)
	{
		next_table[index] = (int *)malloc(sizeof(int) * 3);
		ft_bzero(next_table[index], sizeof(int) * 3);
		if (!(index % 2))
			next_table[index][0] = next_upper_half(pivot[0 + (index > 1)], \
					pivot[1 + (index > 1)], data->stack[STACK_ID_A]);
		if (index % 2)
		{
			next_table[index][0] = next_lower_half(pivot[0 + (index > 1)], \
					pivot[1 + (index > 1)], data->stack[STACK_ID_A]);
			next_table[index][1] = 1;
		}
		next_table[index][0] += 1 * (next_table[index][0] != -1) * !(index > 1);
		next_table[index][2] = !(index > 1);
		index++;
	}
	return (next_table);
}

static void	selection_sort_prev_step(int pivot[3], t_data *data)
{
	int	**next_table;
	int	index;

	while (data->stack[STACK_ID_A].size)
	{
		index = 0;
		next_table = selection_sort_prev_table(pivot, data);
		heap_sort(next_table, 4);
		while (index < 4 && next_table[index][0] == -1)
			index++;
		if (index == 4 && next_table[index - 1][0] == -1)
			break ;
		if (index > 3)
			index = 3;
		exec_instr_loop(ROT_ID + (next_table[index][1] == 1), STACK_ID_A, \
				next_table[index][0] - (next_table[index][2] == 1), data);
		exec_instr_loop(PUSH_ID, STACK_ID_B, 1, data);
		if (next_table[index][2] == 1)
			exec_instr_loop(ROT_ID, STACK_ID_B, 1, data);
		free_table(next_table, 4);
	}
	free_table(next_table, 4);
}

static void	sort_start_loop(t_data *data)
{
	int	index;
	int	median;
	int	*pivot;
	int	pivot_step[3];

	index = 0;
	median = ((data->n_steps + 1) / 2) - (data->n_steps % 2);
	pivot = pivot_get(data->stack[STACK_ID_A], data->n_steps);
	while (index < median)
	{
		pivot_step[0] = pivot[median - (index + 1)];
		pivot_step[1] = pivot[median];
		pivot_step[2] = pivot[median + (index + 1)];
		selection_sort_prev_step(pivot_step, data);
		index++;
	}
	free(pivot);
}

void	sort_start(t_data *data)
{
	if (check_if_sorted(data->stack[STACK_ID_A], data->stack[STACK_ID_A].size))
		return ;
	if (data->stack[STACK_ID_A].size < SMALL_LIMIT)
	{
		selection_sort(data, STACK_ID_A);
		exec_instr_loop(PUSH_ID, 0, data->stack[STACK_ID_B].size, data);
		return ;
	}
	sort_start_loop(data);
	exec_instr_loop(PUSH_ID, STACK_ID_B, data->stack[STACK_ID_A].size, data);
	selection_sort(data, STACK_ID_B);
}
