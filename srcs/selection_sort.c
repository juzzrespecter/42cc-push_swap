#include "push_swap.h"

static int	find_smallest(t_stack stack)
{
	int	i;
	int	smallest;
	int	smallest_pos;

	i = 0;
	smallest = stack_ud(stack, 0);
	while (i < stack.size)
	{
		if (stack_ud(stack, i) < smallest)
		{
			smallest = stack_ud(stack, i);
			smallest_pos = i;
		}
		i++;
	}
	return (smallest_pos);
}

static void	sort_three(t_stack stack, t_data *data) // check this
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_ud(stack, 0);
	while (i < 3)
	{
		if (stack_ud(stack, i) > biggest)
		{
			biggest = stack_ud(stack, i);
			biggest_pos = i;
		}
		i++;
	}
	if (biggest_pos != 2)
		exec_instr_loop(ROT_ID + (biggest_pos == 1), S_A, 1, data);
	if (stack_ud(stack, 0) > stack_ud(stack, 1))
		exec_instr_loop(SWAP_ID, S_A, 1, data);
}

static void	selection_sort_step(t_data *data)
{
	int pos;

	if (data->stack[S_A].size == 0)
		return ;
	if (check_already_sorted(data->stack[S_A], data->stack[S_A].size))
		return ;
	if (data->stack[S_A].size == 2)
	{
		exec_instr_loop(SWAP_ID, S_A, 1, data);
		return ;
	}
	if (data->stack[S_A].size == 3)
	{
		sort_three(data->stack[S_A], data);
		return ;
	}
	pos = find_smallest(data->stack[S_A]);
	if (pos < data->stack[S_A].size / 2)
		exec_instr_loop(ROT_ID, S_A, pos, data);
	else
		exec_instr_loop(RROT_ID, S_A, data->stack[S_A].size - pos, data);
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	selection_sort_step(data);
}

static double	choose_pivot(t_stack stack, int recorrido)
{
	double	median;
	int		i;

	median = 0;
	i = 0;
	while (i < recorrido)
	{
		median += stack_ud(stack, i);
		i++;
	}
	median /= (double)recorrido;
	return (median);
}

static int	find_biggest(t_stack stack)
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_ud(stack, 0);
	while (i < stack.size)
	{
		if (stack_ud(stack, i) > biggest)
		{
			biggest = stack_ud(stack, i);
			biggest_pos = i;
		}
		i++;
	}
	return (biggest_pos);
}

static void	selection_sort_b(t_data *data)
{
	int		pos;
	t_stack	stack;

	stack = data->stack[S_B];
	if (stack.size == 0)
		return ;
	if (stack.size == 2)
	{
		if (stack_ud(stack, 0) < stack_ud(stack, 1))
			exec_instr_loop(SWAP_ID, S_B, 1, data);
		exec_instr_loop(PUSH_ID, S_A, 2, data);
		return ;
	}
	pos = find_biggest(data->stack[S_B]);
	if (pos < stack.size / 2)
		exec_instr_loop(ROT_ID, S_B, pos, data);
	else
		exec_instr_loop(RROT_ID, S_B, stack.size - pos, data);
	exec_instr_loop(PUSH_ID, S_A, 1, data);
	selection_sort_b(data);
}

static int	find_next_up(t_stack stack, double pivot)
{
	int	pos;

	pos = 0;
	while (pos < stack.size)
	{
		if ((double)stack_ud(stack, pos) < pivot)
			return pos;
		pos++;
	}
	return (-1);
}

static int	find_next_down(t_stack stack, double pivot)
{
	int	pos;

	pos = 0;
	while (pos < stack.size)
	{
		if ((double)stack_ud(stack, stack.size - pos - 1) < pivot)
			return pos + 1;
		pos++;
	}
	return (-1);
}

static void	split_array(t_data *data)
{
	double	pivot, pivot_paso;
	int	size;
	int		i, j;
	int	next_up, next_down;

	pivot = 0;
	i = 0;
	j = 0;
	size = data->stack[S_A].size;
	pivot = choose_pivot(data->stack[S_A], data->stack[S_A].size);
	while (j < 5)
	{
		pivot_paso = (j + 1) * (pivot / 3);
		while (i < size)
		{
			next_up = find_next_up(data->stack[S_A], pivot_paso);
			if (next_up == -1)
				break ;
			next_down = find_next_down(data->stack[S_A], pivot_paso);
			if (next_up < next_down)
				exec_instr_loop(ROT_ID, S_A, next_up, data);
			else
				exec_instr_loop(RROT_ID, S_A, next_down, data);
			exec_instr_loop(PUSH_ID, S_B, 1, data);
			i++;
		}
		j++;
	}
}

/*void	selection_sort(t_data *data)
  {
  int	n;

//	selection_sort_step(data);
//	exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
// 1. - parte el array en dos: (a) con < pivot, (b) con >= pivot
split_array(data);
n = data->stack[S_A].size;
// 2. - selection sort en (a)
selection_sort_step(data);
n += -1 * (data->stack[S_A].size);
// 3. - push b (a) en stack (a)
exec_instr_loop(PUSH_ID, S_A, n, data);
// 4. - selection sort en (b)
selection_sort_b(data);	
}*/

void	selection_sort(t_data *data)
{
	// parte en 4
	// selection sort en b:

	split_array(data);
	selection_sort_step(data);
	selection_sort_b(data);
}
