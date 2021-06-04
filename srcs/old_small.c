#include "push_swap.h"

int	test_save_rotations(int stack_id, t_data *data, int step);

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
	static int	( *check_redundant_rot[])(t_stack, int) = {
		find_smallest_number,
		find_biggest_number
	};
	int	push_index;

	if (pass < 1)
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
	push_index = check_redundant_rot[stack_id](data->stack[stack_id], pass);
	if (push_index != -1)
	{
	if (push_index > pass / 2)
		exec_instr_loop(RROT_ID, stack_id, pass - push_index, data);
	else
		exec_instr_loop(ROT_ID, stack_id, push_index, data);
	exec_instr_loop(PUSH_ID, 1 * (stack_id == 0), 1 , data);
	}
	selection_sort_small(data, stack_id, pass - 1);	
}

/*
 * rotaciones redundantes:
 *
 * pos_2 < pos_1 en la misma mitad del stack
 * [ 0 -> pos_2], [pos_2 -> pos_1]
 * 		r * { [ 0 -> pos_2 ] + [pos_2 -> pos_1] }
 *		p
 *		rr * [pos_2 ->pos_1]
 *		p
 *
 *		r * [0 -> pos_2 ]
 *		p
 *		r * [pos_2 -> pos_1]
 *		p
 *		s
 *
 */

