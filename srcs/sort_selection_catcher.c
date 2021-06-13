#include "push_swap.h"

void	push_swap_one(t_data *data, t_instr instr_set, int id)
{
	exec_instr_loop(ROT_ID + instr_set.fp, id, instr_set.P1, data);
	exec_instr_loop(PUSH_ID, (id == STACK_ID_A), 1, data);
	exec_instr_loop(SWAP_ID, (id == STACK_ID_A), 1, data);
}

static int	selection_catcher_pos(int n_to_push, int id, t_stack stack)
{
	int	insertion_pos;

	insertion_pos = 0;
	if (id == STACK_ID_A)
	{
		while (pos < stack.size && stack_ud(stack, insertion_pos) > n_to_push)
			insertion_pos++;
	}
	if (id == STACK_ID_B)
	{
		while (pos < data->stack[(id == STACK_ID_A)].size && \
				stack_ud(data->stack[(id == STACK_ID_A)], pos) < instr_set.next)
			insertion_pos++;
	}
	return (insertion_pos);
}

void	selection_sort_catcher(t_data *data, t_instr instr_set, int id)
{
	int insertion_pos = 0;

	insertion_pos = selection_catcher_pos(instr_set.next, id, data->stack[id]);
	if (pos == 1)
	{
		push_swap_one(data, instr_set, id);
		return ;
	}
	if (pos > data->stack[(id == STACK_ID_A)].size / 2)
	{
		pos = data->stack[(id == STACK_ID_A)].size - pos;
		instr_set.C2 = 1;
		instr_set.fc = 1;
	}
	instr_set.C1 = pos;
	instr_set.C2 += pos;
	if (instr_set.fc == instr_set.fp)
	{
		int	rot_two;
		rot_two = (instr_set.C1 > instr_set.P1) ? instr_set.P1 : instr_set.C1;
		exec_instr_loop(ROT_ID + instr_set.fc, STACK_ID_BOTH, rot_two, data);
		if (instr_set.C1 > instr_set.P1)
			exec_instr_loop(ROT_ID + instr_set.fc, (id == STACK_ID_A), instr_set.C1 - instr_set.P1, data);
		else
			exec_instr_loop(ROT_ID + instr_set.fc, id, instr_set.P1 - instr_set.C1, data);
	}
	else
	{
		exec_instr_loop(ROT_ID + instr_set.fp, id, instr_set.P1, data);
		exec_instr_loop(ROT_ID + instr_set.fc, (id == STACK_ID_A), instr_set.C1, data);
	}
	exec_instr_loop(PUSH_ID, (id == STACK_ID_A), 1, data);
	exec_instr_loop(ROT_ID + (instr_set.fc == 0), (id == STACK_ID_A), instr_set.C2, data);
}
