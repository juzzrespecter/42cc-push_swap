#include "push_swap.h"

static void	init_pivot_a(t_stack stack, int *pivot_a, int n_steps)
{
	int	i;
	int	*heap;

	i = 0;
	heap = heap_sort(stack.array, stack.size, stack.size);
	while (i < n_steps)
	{
		pivot_a[i] = heap[i  * (stack.size / n_steps)];
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

static void	selection_sort_prev_step(int pivot_a[3], t_data *data)
{
	int	*pos_array[4];
	int	index;

	while (1)
	{
		index = 0;
		while (index < 4)
		{
			pos_array[index] = (int *)malloc(sizeof(int) * 3);
			ft_bzero(pos_array[0], sizeof(int) * 3);
			if (!index % 2)
				pos_array[index][0] = next_upper_half(pivot_a[0 + (index > 1)], pivot_a[1 + (index > 1)], data->stack[STACK_ID_A]);
			if (index % 2)
			{
				pos_array[index][0] = next_lower_half(pivot_a[0 + (index > 1)], pivot_a[1 + (index > 1)], data->stack[STACK_ID_A]);
				pos_array[index][1] = 1;
			}
			pos_array[index][0] += 1 * (pos_array[index][0] != -1) * (index < 2);
			pos_array[index][2] = (index > 1);
			index++;
		}

		/*index = 0;
		pos_array[0] = (int *)malloc(sizeof(int) * 3);
		pos_array[1] = (int *)malloc(sizeof(int) * 3);
		pos_array[2] = (int *)malloc(sizeof(int) * 3);
		pos_array[3] = (int *)malloc(sizeof(int) * 3);
		ft_bzero(pos_array[0], sizeof(int) * 3);
		ft_bzero(pos_array[1], sizeof(int) * 3);
		ft_bzero(pos_array[2], sizeof(int) * 3);
		ft_bzero(pos_array[3], sizeof(int) * 3);

		pos_array[0][0] = next_upper_half(pivot_a[0], pivot_a[1], data->stack[STACK_ID_A]);
		pos_array[0][0] += 1 * (pos_array[0][0] != -1);
		pos_array[1][0] = next_lower_half(pivot_a[0], pivot_a[1], data->stack[STACK_ID_A]);
		pos_array[1][0] += 1 * (pos_array[1][0] != -1);
		pos_array[2][0] = next_upper_half(pivot_a[1], pivot_a[2], data->stack[STACK_ID_A]);
		pos_array[3][0] = next_lower_half(pivot_a[1], pivot_a[2], data->stack[STACK_ID_A]);

		pos_array[0][2] = 1;
		pos_array[1][2] = 1;

		pos_array[1][1] = 1;
		pos_array[3][1] = 1;
*/
		heap_sort(pos_array, 4);
		while (index < 4 && pos_array[index][0] == -1)
			index++;
		if (index == 4 && pos_array[index - 1][0] == -1)
			break ;
		exec_instr_loop(ROT_ID + (pos_array[index][1] == 1), STACK_ID_A, pos_array[index][0] - (pos_array[index][2] == 1), data);
		exec_instr_loop(PUSH_ID, STACK_ID_B, 1, data);
		if (pos_array[index][2] == 1)
			exec_instr_loop(ROT_ID, STACK_ID_B, 1, data);
		free_table(pos_array);
	}
}

void	sort_start(t_data *data)
{
	int pivot_a[data->n_steps];
	int	pivot_a_step[3];
	int	index;

	if (check_if_sorted(data->stack[STACK_ID_A], data->stack[STACK_ID_A].size))
		return ;
	if (data->stack[STACK_ID_A].size < SMALL_LIMIT)
	{
		data->n_ins = 1; // tmp
		selection_sort(data, STACK_ID_A);
		exec_instr_loop(PUSH_ID, STACK_ID_A, data->stack[STACK_ID_B].size, data);
		return ;
	}
	init_pivot_a(data->stack[STACK_ID_A], pivot_a, data->n_steps);
	ft_bzero(pivot_a_step, sizeof(int) * 3);
	index = 0;
	while (index < data->n_steps / 2 )
	{
		pivot_a_step[0] = pivot_a[(data->n_steps / 2) - (index + 1)];
		pivot_a_step[1] = pivot_a[data->n_steps / 2];
		pivot_a_step[2] = pivot_a[(data->n_steps / 2) + (index + 1)];
		selection_sort_prev_step(pivot_a_step, data);
		index++;
	}
	exec_instr_loop(PUSH_ID, STACK_ID_B, data->stack[STACK_ID_A].size, data);  // check this
	selection_sort(data, STACK_ID_B);
}