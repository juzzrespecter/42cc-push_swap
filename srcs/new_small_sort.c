#include "push_swap.h"

typedef struct { int ROT_A, ROT_B, LOW_A, LOW_B; } t_test;

t_test libreta = {
	.ROT_A = 0,
	.ROT_B = 0,
	.LOW_A = 0,
	.LOW_B = 0
};

static void	sort_three(t_data *data, int step)
{
	int rot_position;

	if (step == 3)
	{
		rot_position = find_biggest_number(data->stack[S_A], 3);
		if (rot_position != 2)
			exec_instr_loop(ROT_ID + (rot_position == 1), S_A, 1, data);
	}
	if (stack_ud(data->stack[S_A], 0) > stack_ud(data->stack[S_A], 1))
		exec_instr_loop(SWAP_ID, S_A, 1, data);
}

void	insert_to_sorted_stack(t_data *data, int id, int to_sort)
{
	int	pos;

//	to_sort = stack_ud(data->stack[id], 0);
	pos = 0;
	while (id == S_A && to_sort < stack_ud(data->stack[(id == S_A)], pos))
		pos++;
	while (id == S_B && to_sort > stack_ud(data->stack[(id == S_A)], pos))
		pos++;
	if (data->stack[(id == S_A)].size == 0)
		pos = 0;
	if (pos == 1)
	{
		exec_instr_loop(PUSH_ID, (id == S_A), 1, data);
		exec_instr_loop(SWAP_ID, (id == S_A), 1, data);
	}
	else
	{
		//	(id == S_A) ? libreta.ROT_B = pos : libreta.ROT_A = pos;
		if (id == S_A)
			libreta.ROT_B = pos;
		else
			libreta.ROT_A = pos;
		//exec_instr_loop(ROT_ID, (id == S_A), pos, data);
		exec_instr_loop(ROT_ID, S_BOTH, (libreta.ROT_A > libreta.ROT_B) \
				? libreta.ROT_B : libreta.ROT_A, data);
		(libreta.ROT_A > libreta.ROT_B) ? \
			exec_instr_loop(ROT_ID, S_A, libreta.ROT_A - libreta.ROT_B, data) : \
			exec_instr_loop(ROT_ID, S_B, libreta.ROT_B - libreta.ROT_A, data);
		printf("R\tlibreta (%d, %d)\n",\
				libreta.ROT_A, libreta.ROT_B);
		libreta.ROT_A = 0;
		libreta.ROT_B = 0;
		//		exec_instr_loop(ROT_ID, S_A, libreta.ROT_A, data);
		//		exec_instr_loop(ROT_ID, S_B, libreta.ROT_B, data);
		exec_instr_loop(PUSH_ID, (id == S_A), 1, data);
		if (id == S_A)
			libreta.RROT_B = pos;
		else
			libreta.RROT_A = pos;
		//exec_instr_loop(RROT_ID, (id == S_A), pos, data);
	}
}

int	test_n = 3;

void	small_sort(t_data *data, int id)
{
	int	**next_table;
	int	**index_table;

	/*
	 *find three next
	 *select the nearest
	 *insertion_sort
	 *recursive
	 */

	if (data->stack[id].size < 1)
		return ;
	if (data->stack[id].size < 4 && id == S_A)
	{
		sort_three(data, data->stack[S_A].size);
		return ;
	}

	//	set up tables

	index_table = get_index_table(data->stack[id].array, data->stack[id].size);

	next_table = (int **)malloc(sizeof(int *) * test_n);

	int	i = 0;
	while (i < test_n)
	{
		next_table[i] = (int *)malloc(sizeof(int) * 2);

		ft_bzero(next_table[i], sizeof(int) * 2);
		i++;
	}

	//	get next three positions

	i = 0;
	while (i < test_n)
	{
		if (data->stack[id].size > i)
			next_table[i][0] = index_table[i * (id == S_A) + (data->stack[id].size - (i + 1)) * (id == S_B)][1];
		else
			next_table[i][0] = -1;
		i++;
	}

	//	translate to relative position

	i = 0;
	while (i < test_n)
	{
		if (next_table[i][0] > data->stack[id].size / 2)
		{
			next_table[i][0] = data->stack[id].size - next_table[i][0];
			next_table[i][1] = 1;
		}
		i++;
	}

	insertion_sort(next_table, test_n, 0);
	i = 0;
	while (next_table[i][0] == -1)
		i++;
	int to_sort;
	if (next_table[i][1] == 1)
	{
		if (id == S_A) {
			libreta.RROT_A = next_table[i][0];
			to_sort = stack_ud(data->stack[S_A], data->stack[S_A].size - libreta.RROT_A);
		}
		else {
			libreta.RROT_B = next_table[i][0];
			to_sort = stack_ud(data->stack[S_B], data->stack[S_B].size - libreta.RROT_B);
		}
	}
	//exec_instr_loop(ROT_ID + (next_table[i][1] == 1), id, next_table[i][0], data);
	else
	{
		if (id == S_A)
		{
			libreta.ROT_A = next_table[i][0];
			to_sort = stack_ud(data->stack[S_A], libreta.ROT_A);
		}
		else
		{
			libreta.ROT_B = next_table[i][0];
			to_sort = stack_ud(data->stack[S_B], libreta.ROT_B);
		}
		//(id == S_A) ? libreta.ROT_A = next_table[i][0] : libreta.ROT_B = next_table[i][0];
	}

	exec_instr_loop(RROT_ID, S_BOTH, (libreta.RROT_A > libreta.RROT_B) \
			? libreta.RROT_B : libreta.RROT_A, data);
	(libreta.RROT_A > libreta.RROT_B) ? \
		exec_instr_loop(RROT_ID, S_A, libreta.RROT_A - libreta.RROT_B, data) : \
		exec_instr_loop(RROT_ID, S_B, libreta.RROT_B - libreta.RROT_A, data);
		printf("RR\tlibreta (%d, %d)\n",\
				libreta.RROT_A, libreta.RROT_B);
	libreta.RROT_A = 0;
	libreta.RROT_B = 0;
	insert_to_sorted_stack(data, id, to_sort);
	small_sort(data, id);
}
