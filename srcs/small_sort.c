#include "push_swap.h"

static void	sort_three(t_data *data)
{
	int rot_position;

	rot_position = find_biggest_number(data->stack[S_A], 3);
	if (rot_position != 2)
		exec_instr_loop(ROT_ID + (rot_position == 1), S_A, 1, data);
	if (stack_ud(data->stack[S_A], 0) > stack_ud(data->stack[S_A], 1))
		exec_instr_loop(SWAP_ID, S_A, 1, data);
}

void	selection_sort_small(t_data *data, int stack_id, int pass)
{
	int	push_index;

	if (pass == 0)
		return ;
	if (pass == 2 && stack_id == S_A)
	{
		if (stack_ud(data->stack[stack_id], 0) > stack_ud(data->stack[stack_id], 1))
			exec_instr_loop(SWAP_ID, stack_id, 1, data);
		return ;
	}
	if (pass == 3 && stack_id == S_A)
	{
		sort_three(data);
		return ;
	}
	if (stack_id == S_A)
		push_index = find_smallest_number(data->stack[stack_id], pass);
	else
		push_index = find_biggest_number(data->stack[stack_id], pass);
	if (push_index > pass / 2)
		exec_instr_loop(RROT_ID, stack_id, pass - push_index, data);
	else
		exec_instr_loop(ROT_ID, stack_id, push_index, data);
	exec_instr_loop(PUSH_ID, 1 * (stack_id == 0), 1, data);
	selection_sort_small(data, stack_id, pass - 1);
}
