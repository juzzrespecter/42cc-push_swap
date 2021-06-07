#include "push_swap.h"

int	test_save_rotations(int stack_id, t_data *data, int step);
typedef struct	s_count { int ROT, RROT, PUSH, SWAP; } t_count;

static t_count notario = { .ROT = 0,
	.RROT = 0,
	.PUSH = 0,
	.SWAP = 0
};

/*void	print_instr(t_count n)
{
	printf("N ROT: (%d)\nN RROT: (%d)\nN PUSH (%d)\nN SWAP: (%d)\n",\
			n.ROT, n.RROT, n.PUSH, n.SWAP);
	printf("-------\nTOTAL: (%d)\n-------\n", n.ROT + n.RROT + n.PUSH + n.SWAP);
	notario = (t_count) { .ROT = 0,
		.RROT = 0,
		.PUSH = 0,
		.SWAP = 0
	};
}*/

void print_stack(t_stack stack, int size) { int i = 0; while (i < size) { printf("%d\n", stack_ud(stack, i)); i++; } }


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
	{
//		print_instr(notario);
		return ;
	}
	if (pass == 2 && stack_id == S_A)
	{
		if (stack_ud(data->stack[stack_id], 0) > stack_ud(data->stack[stack_id], 1))
			exec_instr_loop(SWAP_ID, stack_id, 1, data);
//		print_instr(notario);
		return ;
	}
	if (pass == 3 && stack_id == S_A)
	{
		sort_three(data);
//		print_instr(notario);
		return ;
	}
	if (check_if_sorted(data->stack[stack_id], pass) && (stack_id == S_A)) {
//		print_instr(notario);
		return ;
	}
	//push_index = check_redundant_rot[stack_id](data->stack[stack_id], pass);
//	printf("----------------- pass (%d) --------------------\n", pass);
//	print_stack(data->stack[stack_id], data->stack[stack_id].size);
	push_index = test_save_rotations(stack_id, data, pass);
	if (push_index != -1)
	{
		if (push_index > pass / 2)
		{
			exec_instr_loop(RROT_ID, stack_id, pass - push_index, data);
			notario.RROT += pass - push_index;
		}
		else
		{
			exec_instr_loop(ROT_ID, stack_id, push_index, data);
			notario.ROT += push_index;
		}
		exec_instr_loop(PUSH_ID, 1 * (stack_id == 0), 1 , data);
		notario.PUSH += 1;
//	print_instr(notario);
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
	int on_lower_half, on_upper_half;

	int pos_1;
	int pos_2;

	t_stack stack = data->stack[stack_id];

	static int	(* pos_finder[])(t_stack, int, int) = {
		cool_find_smallnum,
		cool_find_bignum
	};

	pos_1 = pos_finder[stack_id](data->stack[stack_id], step, -1);
	pos_2 = pos_finder[stack_id](data->stack[stack_id], step, pos_1);
	on_lower_half = (pos_2 > stack.size / 2 && pos_1 > stack.size / 2);
	on_upper_half = (pos_2 < stack.size / 2 && pos_1 < stack.size / 2);

	if (pos_2 < pos_1 && on_upper_half)
	{
		exec_instr_loop(ROT_ID, stack_id, pos_2, data);
		notario.ROT += pos_2;
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
		notario.PUSH += 1;
		exec_instr_loop(ROT_ID, stack_id, pos_1 - pos_2 - 1, data);
		notario.ROT += pos_1 - pos_2 - 1;
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
		notario.PUSH += 1;
		exec_instr_loop(SWAP_ID, (stack_id == 0), 1, data);
		notario.SWAP += 1;
		return (-1);
	}
	if (pos_2 > pos_1 && on_lower_half)
	{
		exec_instr_loop(RROT_ID, stack_id, stack.size - pos_2, data);
		notario.RROT = stack.size - pos_2;
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
		notario.PUSH += 1;
		exec_instr_loop(RROT_ID, stack_id, (stack.size - pos_1) - (stack.size - pos_2), data);
		notario.RROT += (stack.size - pos_1) - (stack.size - pos_2);
		exec_instr_loop(PUSH_ID, (stack_id == 0), 1, data);
		notario.PUSH += 1;
		exec_instr_loop(SWAP_ID, (stack_id == 0), 1, data);
		notario.SWAP += 1;
		return (-1);
	}
	return (pos_1);
}
