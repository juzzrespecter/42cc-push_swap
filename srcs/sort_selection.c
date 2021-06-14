#include "push_swap.h"

static int	**selection_sort_next(t_stack stack, int n_ins, int id)
{
	int	**next_table;
	int	**index_table;
	int	i;

	next_table = (int **)malloc(sizeof(int) * n_ins);
	index_table = get_index_table(stack.array, stack.size);
	i = 0;
	while (i < n_ins)
	{
		next_table[i] = (int *)malloc(sizeof(int) * 2);
		ft_bzero(next_table[i], sizeof(int) * 2);
		next_table[i][0] = -1;
		if (stack.size > i)
		{
			if (id == STACK_ID_A)
				next_table[i][0] = index_table[i][1];
			else
				next_table[i][0] = index_table[stack.size - (i + 1)][1];
		}
		if (next_table[i][0] > stack.size / 2)
		{
			next_table[i][0] = stack.size - next_table[i][0];
			next_table[i][1] = 1;
		}
		i++;
	}
	return (next_table);
}

static t_instr	selection_sort_moves(int *next_to_push, int id, t_data *data)
{
	t_instr	set;
	int		stack_n;

	ft_bzero(&set, sizeof(t_instr));
	set.P1 = next_to_push[0];
	set.fp = next_to_push[1];
	if (set.fp)
		stack_n = stack_ud(data->stack[id], data->stack[id].size - set.C1);
	else
		stack_n = stack_ud(data->stack[id], set.P1);
	set.C1 = next_catcher(stack_n, id, data);
	if (set.C1 > data->stack[!id].size)
	{
		set.C1 = data->stack[!id].size - set.C1;
		set.C2 = 1;
		set.fc = 1;
	}
	set.C2 += set.C1;
	return (set);
}

void	push_swap_one(t_data *data, t_instr set, int id)
{
	exec_instr_loop(ROT_ID + set.fp, id, set.P1, data);
	exec_instr_loop(PUSH_ID, !id, 1, data);
	exec_instr_loop(SWAP_ID, !id, 1, data);
}

static void	selection_sort_push(t_instr set, int id, t_data *data)
{
	int	rot_both;

	rot_both = 0;
	if (set.C1 && !set.fc)
	{
		push_swap_one(data, set, id);
		return ;
	}
	if (set.fc == set.fp && set.C1 > set.P1)
	{
		rot_both = set.P1;
		set.P1 = 0;
		set.C1 = set.C1 - set.P1;
	}
	if (set.fc == set.fp && set.C1 < set.P1)
	{
		rot_both = set.C1;
		set.P1 = set.C1 - set.P1;
		set.C1 = 0;
	}
	exec_instr_loop(ROT_ID + set.fc, STACK_ID_BOTH, rot_both, data);
	exec_instr_loop(ROT_ID + set.fp, id, set.P1, data);
	exec_instr_loop(ROT_ID + set.fc, !id, set.C1, data);
	exec_instr_loop(PUSH_ID, !id, 1, data);
	exec_instr_loop(ROT_ID + set.fc, !id, set.C2, data);
}

void	selection_sort(t_data *data, int id)
{
	t_instr	set;
	int		**next_table;
	int		i;

	if (data->stack[id].size < 1)
		return ;
	if (data->stack[id].size < 4 && id == STACK_ID_A)
	{
		sort_three(data, data->stack[STACK_ID_A]);
		return ;
	}
	next_table = selection_sort_next(data->stack[id], data->n_ins, id);
	heap_sort(next_table, data->n_ins);
	i = 0;
	while (next_table[i][0] == -1 && i < data->n_ins)
		i++;
	set = selection_sort_moves(next_table[i], id, data);
	selection_sort_push(set, id, data);
	selection_sort(data, id);
}
