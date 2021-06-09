#include "push_swap.h"
#define N_PASOS 6

typedef struct	s_next
{
	int	n_rot;
	int	rel_pos;
	int	to_bottom;
}		t_next;

typedef struct 	s_step
{
	int	pivot[2];
	int	*array;
	int	size;
	t_next	next_array[4];
}		t_step;

void	print_heap(int *heap, int n) // delete when finished
{
	int i = 0;
	while (i < n) { printf("(%d)\n", heap[i]); i++; }
}

static void	init_pivot_array(t_stack stack, int *pivot_array)
{
	int	i;
	int	*heap;

	i = 0;
	heap = heap_sort(stack.array, stack.size, stack.size);
	while (i < N_PASOS)
	{
		pivot_array[i] = heap[(i + 1) * (stack.size / N_PASOS) - 1];
		i++;
	}
	free(heap);
}

/*static int	find_next_down(int pivot, int chunk_size, int index, t_stack stack)
{
	int	pos;

	pos = 0;
	while (pos < chunk_size)
	{
		if (stack_ud(stack, index - pos) < pivot)
			return (pos + 1);
		pos++;
	}
	return (-1);
}*/

/*
 * 1. choose pivots
 * 2. search for element { upper, lower, upper (big), lower (big) }
 * 3. sort pos array
 * 4. choose first non -1
 * 5. exec (n_rot, push 1, n_rot 1 if big)
 *
 */

static int	next_upper_half(int pivot_max, int pivot_min, t_stack stack)
{
	int	index;
	int	n;

	while (index < stack.size)
	{
		n = stack_ud(stack, index);
		if (n >= pivot_min && n <= pivot_max)
			return (index);
		index++;
	}
	return (-1);
}

static int	next_lower_half(int pivot_max, int pivot_min, int size)
{
	int	index;
	int	n;

	index = 0;
	n = stack_ud(
}

static void	selection_sort_medium_step(int pivot, t_data *data)
{
	int	next_pos[4];

	while (1)
	{
		ft_bzero(next_pos_big, sizeof(int) * 2);
		ft_bzero(next_pos_small, sizeof(int) * 2);
		next_up = find_next_up( pivot,  data->stack[S_A].size, data->stack[S_A]);
		next_down = find_next_down( pivot, data->stack[S_A].size, data->stack[S_A].size - 1,  data->stack[S_A]);
		if (next_down == -1 && next_up == -1)
			break ;
		if ((next_down < next_up && next_down != -1) || (next_up == -1 && next_down != -1))
			exec_instr_loop(RROT_ID, S_A, next_down, data);
		else
			exec_instr_loop(ROT_ID, S_A, next_up, data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
	}
}

void	selection_sort_medium(t_data *data)
{
	int pivot[N_PASOS];
	int	i;

	init_pivot_array(data->stack[S_A], pivot);
	i = 0;
	selection_sort_medium_step(pivot[N_PASOS / 2 - 1], pivot[N_PASOS / 2], \
			pivot[N_PASOS / 2 + 1], data);
//	selection_sort_small(data, S_A, data->stack[S_A].size);
//	selection_sort_small(data, S_B, data->stack[S_B].size);
}
