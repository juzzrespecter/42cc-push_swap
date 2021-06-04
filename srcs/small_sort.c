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
	/*static int	( *check_redundant_rot[])(t_stack, int) = {
		find_smallest_number,
		find_biggest_number
	};*/
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
	//push_index = check_redundant_rot[stack_id](data->stack[stack_id], pass);
	push_index = test_save_rotations(stack_id, data, pass);
	if (push_index != -1)
	{
	if (push_index > pass / 2)
		exec_instr_loop(RROT_ID, stack_id, pass - push_index, data);
	else
		exec_instr_loop(ROT_ID, stack_id, push_index, data);
	exec_instr_loop(PUSH_ID, 1 * (stack_id == 0), 1 , data);
	}
	selection_sort_small(data, stack_id, pass - 1 - (push_index == -1));	
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

typedef struct	s_count { int ROT, RROT, PUSH, SWAP; } t_count;

int	cool_find_bignum(t_stack stack, int step, int no_i)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < step)
	{
		if (i != no_i && stack_ud(stack, i) > stack_ud(stack, pos))
			pos = i;
		i++;
	}
	return (pos);
}

int	cool_find_smallnum(t_stack stack, int step, int no_i)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (i < step)
	{
		if (i != no_i && stack_ud(stack, i) < stack_ud(stack, pos))
			pos = i;
		i++;
	}
	return (pos);
}

int	test_save_rotations(int stack_id, t_data *data, int step)
{
	//find_1(); -> find biggest / smallest
	//find_2(); -> find second biggest / smallest
	int on_lower_half;
	t_count	notario;

	int pos_1;
	int pos_2;

	t_stack stack = data->stack[stack_id];

	static int	(* pos_finder[])(t_stack, int, int) = {
		cool_find_bignum,
		cool_find_smallnum
	};

	ft_bzero(&notario, sizeof(t_count));

	pos_1 = pos_finder[stack_id](data->stack[stack_id], step, -1);
	pos_2 = pos_finder[stack_id](data->stack[stack_id], step, pos_1);
	on_lower_half = (pos_2 > stack.size / 2 && pos_1 > stack.size / 2);

	if (pos_2 < pos_1 && !on_lower_half)
	{
			//rot(pos_2);
		exec_instr_loop(ROT_ID, stack_id, pos_1, data);
		notario.ROT = pos_1;
			//push();
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
		notario.PUSH = 1;
			//rot(pos_1 - pos_2);
		exec_instr_loop(ROT_ID, stack_id, pos_1, data);
		notario.ROT = pos_1 - pos_2;
			//push();
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
		notario.PUSH += 1;
			//swap();
		exec_instr_loop(SWAP_ID, (stack_id == 0), 1, data);
		notario.SWAP = 1;
		return (-1);
	}
	if (pos_2 > pos_1 && on_lower_half)
	{
			//rrot(size - pos_2);
		exec_instr_loop(RROT_ID, stack_id, stack.size - pos_2, data);
			//push();
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
			//rrot(size - pos_2 - pos_1);
		exec_instr_loop(RROT_ID, stack_id, stack.size - pos_2 - pos_1, data);
			//push();
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
			//swap();
		exec_instr_loop(SWAP_ID, (stack_id == 0), 1, data);
		return (-1);
	}
	return (pos_1);
}
