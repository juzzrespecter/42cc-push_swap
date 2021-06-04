#include "push_swap.h"
# define N_PASOS 7 

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
	/* debug: print heap, print pivots 
	printf("pre calc: (%d) (%d) (%d) [size, n_pasos, division]\n", stack.size, N_PASOS,\
			stack.size / N_PASOS);
	print_heap(heap, stack.size);
	printf("0: (%d), 1: (%d), 2: (%d), 3: (%d), 4: (%d), 5(%d)\n",\
			pivot_array[0], pivot_array[1], pivot_array[2], pivot_array[3], pivot_array[4], \
			pivot_array[5]); */
	free(heap);
}

static int	find_next_down(int pivot, int chunk_size, int index, t_stack stack)
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
}

static void	selection_sort_medium_step(int pivot, t_data *data)
{
	int	next_up;
	int	next_down;

	while (1)
	{
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

//static int ft_abs(int a, int b) { if (a < 0) { a *= -1; } return ((a + b)); }

void	selection_sort_medium(t_data *data)
{
	int pivot[N_PASOS];
//	int	bounds[2];
	int	i;

//	bounds[0] = stack_ud(data->stack[S_A], find_smallest_number(data->stack[S_A], chunk_size));
//	bounds[1] = stack_ud(data->stack[S_A], find_biggest_number(data->stack[S_A], chunk_size));
	init_pivot_array(data->stack[S_A], pivot);
	i = 0;
	printf("stack total size in A: (%d)\n", data->stack[S_A].size);
	while (i < (N_PASOS - 1))
	{
		//pivot = bounds[0] + ( (i + 1) * ft_abs(bounds[0], bounds[1]) ) / N_PASOS;
		selection_sort_medium_step(pivot[i], data);
		i++;
	}
	selection_sort_small(data, S_A, data->stack[S_A].size);
	printf("stack total size in B: (%d)\n", data->stack[S_B].size);
	selection_sort_small(data, S_B, data->stack[S_B].size);
}
