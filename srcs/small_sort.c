#include "push_swap.h"


void print_stack(t_stack stack, int size) { int i = 0; while (i < size) { printf("%d\n", stack_ud(stack, i)); i++; } }

/*
 *	element list:
 *
 *	0 -> position
 *	1 -> rotate to bottom
 *	2 -> on lower half of stack
 *
 */ 

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

void	print_index_table(int **index_table, int stack_size)
{
	int i = 0;
	printf("----it----\n");
	while (i < stack_size)
	{
		printf("(%d, %d)\n", index_table[i][0], index_table[i][1]);
		i++;
	 }
	printf("----it----\n");
}

static int	*set_up_element(int stack_id, t_stack stack, int stack_size)
{
	int		**index_table;
	int	*element;
	int	i;

	i = 0;
	index_table = get_index_table(stack.array, stack_size);
	element = (int *)malloc(sizeof(int) * 2);
	ft_bzero(element, sizeof(int) * 2);
	element[0] = index_table[(stack_size - 1) * (stack_id == S_B)][1];
	if (element[0] > stack_size / 2)
	{
		element[0] = stack_size - element[0];
		element[1] = 1;
	}
	free_index_table(index_table, stack_size);
	return (element);
}

static void	insert_next(int stack_id, t_data *data)
{
	int	i;
	int	*element;

	i = 0;
	element = set_up_element(stack_id, data->stack[stack_id], data->stack[stack_id].size);
	exec_instr_loop(ROT_ID + (element[1] == 1), stack_id, element[0], data);
	exec_instr_loop(PUSH_ID, (stack_id == S_A), 1, data);
	free(element);
}

void	selection_sort_small(t_data *data, int stack_id, int step)
{
	if (step < 1)
		return ;
	if (step < 4 && stack_id == S_A)
	{
		sort_three(data, step);
		return ;
	}
	if (check_if_sorted(data->stack[stack_id], step) && (stack_id == S_A))
		return ;
	insert_next(stack_id, data);
	selection_sort_small(data, stack_id, step - 1);	
}
