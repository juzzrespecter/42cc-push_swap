#include "push_swap.h"

static void	init_pivot_array(t_stack stack, int *pivot_array, int n_steps)
{
	int	i;
	int	*heap;

	i = 0;
	heap = heap_sort(stack.array, stack.size, stack.size);
	while (i < n_steps)
	{
		pivot_array[i] = heap[i  * (stack.size / n_steps)];
		i++;
	}
	free(heap);
}

static int	next_upper_half(int pivot_min, int pivot_max, t_stack stack)
{
	int	index;
	int	n;

	index = 0;
	while (index < stack.size / 2)
	{
		n = stack_ud(stack, index);
		if (n >= pivot_min && n <= pivot_max)
			return (index);
		index++;
	}
	return (-1);
}

static int	next_lower_half(int pivot_min, int pivot_max, t_stack stack)
{
	int	index;
	int	n;

	index = 0;
	while (index < stack.size / 2)
	{
		n = stack_ud(stack, stack.size - (index + 1));
		if (n >= pivot_min && n <= pivot_max)
			return (index + 1);
		index++;
	}
	return (-1);
}

static void	selection_sort_prev_step(int pivot_array[3], t_data *data)
{
	int	*pos_array[4];
	int	index;

	while (1)
	{
		/*
		 * while
		 *		malloc
		 *		clean
		 *		fill {
		 *			pos,
		 *			rel_pos,
		 *			to_bottom
		 *		}
		 * 
		 *
		 */

		/*while (index < 4)
		{
			pos_array[index] = (int *)malloc(sizeof(int) * 3);
			ft_bzero(pos+array[0], sizeof(int) * 3);
			if (!index % 2)
				pos_array[index][0] = next_upper_half(pivot_array
		}*/

		index = 0;
		pos_array[0] = (int *)malloc(sizeof(int) * 3);
		pos_array[1] = (int *)malloc(sizeof(int) * 3);
		pos_array[2] = (int *)malloc(sizeof(int) * 3);
		pos_array[3] = (int *)malloc(sizeof(int) * 3);
		ft_bzero(pos_array[0], sizeof(int) * 3);
		ft_bzero(pos_array[1], sizeof(int) * 3);
		ft_bzero(pos_array[2], sizeof(int) * 3);
		ft_bzero(pos_array[3], sizeof(int) * 3);

		pos_array[0][0] = next_upper_half(pivot_array[0], pivot_array[1], data->stack[S_A]);
		pos_array[0][0] += 1 * (pos_array[0][0] != -1);
		pos_array[1][0] = next_lower_half(pivot_array[0], pivot_array[1], data->stack[S_A]);
		pos_array[1][0] += 1 * (pos_array[1][0] != -1);
		pos_array[2][0] = next_upper_half(pivot_array[1], pivot_array[2], data->stack[S_A]);
		pos_array[3][0] = next_lower_half(pivot_array[1], pivot_array[2], data->stack[S_A]);

		pos_array[0][2] = 1;
		pos_array[1][2] = 1;

		pos_array[1][1] = 1;
		pos_array[3][1] = 1;

		insertion_sort(pos_array, 4, 0);
		while (index < 4 && pos_array[index][0] == -1)
			index++;
		if (index == 4 && pos_array[index - 1][0] == -1)
			break ;
		exec_instr_loop(ROT_ID + (pos_array[index][1] == 1), S_A, pos_array[index][0] - (pos_array[index][2] == 1), data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
		if (pos_array[index][2] == 1)
			exec_instr_loop(ROT_ID, S_B, 1, data);
	}
}

void	sort_start(t_data *data)
{
	int pivot_array[data->n_steps];
	int	pivot_array_step[3];
	int	index;

	if (check_if_sorted(data->stack[S_A], data->stack[S_A].size))
		return ;
	if (data->stack[S_A].size < SMALL_LIMIT)
	{
		data->n_ins = 1; // tmp
		selection_sort(data, S_A);
		exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
		return ;
	}
	init_pivot_array(data->stack[S_A], pivot_array, data->n_steps);
	ft_bzero(pivot_array_step, sizeof(int) * 3);
	index = 0;
	while (index < data->n_steps / 2 )
	{
		pivot_array_step[0] = pivot_array[(data->n_steps / 2) - (index + 1)];
		pivot_array_step[1] = pivot_array[data->n_steps / 2];
		pivot_array_step[2] = pivot_array[(data->n_steps / 2) + (index + 1)];
		selection_sort_prev_step(pivot_array_step, data);
		index++;
	}
	exec_instr_loop(PUSH_ID, S_B, data->stack[S_A].size, data);  // check this
	selection_sort(data, S_B);
}
