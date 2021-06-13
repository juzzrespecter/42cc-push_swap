#include "push_swap.h"

t_instr	reset(void)
{
	t_instr	instr_set;

	instr_set = (t_instr) {
		.P1 = 0,
		.C1 = 0,
		.C2 = 0,
		.fp = 0,
		.fc = 0
	};
	return (instr_set);
}

static void	sort_three(t_data *data, int step)
{
	int	rot_position;

	if (step == 3)
	{
		rot_position = find_biggest_number(data->stack[STACK_ID_A], 3);
		if (rot_position != 2)
			exec_instr_loop(ROT_ID + (rot_position == 1), STACK_ID_A, 1, data);
	}
	if (stack_ud(data->stack[STACK_ID_A], 0) > \
			stack_ud(data->stack[STACK_ID_A], 1))
		exec_instr_loop(SWAP_ID, STACK_ID_A, 1, data);
}

void	selection_sort(t_data *data, int id)
{
	int	**next_table;
	int	**index_table;
	int	i;

	if (data->stack[id].size < 1)
		return ;
	if (data->stack[id].size < 4 && id == STACK_ID_A)
	{
		sort_three(data, data->stack[STACK_ID_A].size);
		return ;
	}
	index_table = get_index_table(data->stack[id].array, data->stack[id].size);
	next_table = (int **)malloc(sizeof(int *) * data->n_ins);
	i = 0;
	while (i < data->n_ins)
	{
		next_table[i] = (int *)malloc(sizeof(int) * 2);
		ft_bzero(next_table[i], sizeof(int) * 2);
		if (data->stack[id].size > i)
			next_table[i][0] = index_table[i * (id == STACK_ID_A) + (data->stack[id].size - (i + 1)) * (id == STACK_ID_B)][1];
		else
			next_table[i][0] = -1;
		if (next_table[i][0] > data->stack[id].size / 2)
		{
			next_table[i][0] = data->stack[id].size - next_table[i][0];
			next_table[i][1] = 1;
		}
		i++;
	}
	heap_sort(next_table, data->n_ins);
	i = 0;
	while (next_table[i][0] == -1)
		i++;

	data->instr_set.P1 = next_table[i][0];
	data->instr_set.fp = next_table[i][1];
	data->instr_set.next = (data->instr_set.fp == 1) ? \
				    stack_ud(data->stack[id], data->stack[id].size - data->instr_set.P1) : \
					stack_ud(data->stack[id], data->instr_set.P1);
	free_table(index_table, data->stack[id].size);
	free_table(next_table, data->n_ins);
	insert_to_catcher(data, data->instr_set, id);
	data->instr_set = reset();
	selection_sort(data, id);
}
