#include "push_swap.h"
# define SMALL_LIMIT 15 
# define MEDIUM_LIMIT 150 

static int	choose_pivot_as_median(t_stack stack, int chunk_size)
{
	int	*heap;
	int	pivot;

	heap = heap_sort(stack.array, stack.size, chunk_size);
	pivot = heap[(chunk_size / 2) - 1];
	free(heap);
	return (pivot);
}

static int	quick_sort_partition(t_data *data,  int chunk_size)
{
	int pivot;
	int	first_step;
	int test;
	int	pos;
	int	i;

	pivot = choose_pivot_as_median(data->stack[S_A], chunk_size);
	i = 0;
	test = 0;
	first_step = (data->stack[S_A].size == chunk_size);
	while (i < chunk_size)
	{
		pos = find_next_up(pivot, chunk_size - i, data->stack[S_A]);
		if (pos < 0)
			break ;
		test += pos;
		exec_instr_loop(ROT_ID, S_A, pos, data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
		i += pos + 1;
	}
	exec_instr_loop(RROT_ID, S_A, test * (first_step == 0), data);
	return (data->stack[S_B].size + 1 * (data->stack[S_B].size == 0));
}

static void	quick_sort(t_data *data,  int chunk_size)
{
	int	n_b;

	if (chunk_size < 2)
	{
		exec_instr_loop(ROT_ID, S_A, 1, data);
		return ;
	}
	if (check_if_sorted(data->stack[S_A], chunk_size))
	{
		exec_instr_loop(ROT_ID, S_A, chunk_size, data);
		return ;
	}
	n_b = quick_sort_partition(data, chunk_size);
	if (n_b < 50)
		selection_sort_small(data, S_B, data->stack[S_B].size);
	exec_instr_loop(PUSH_ID, S_A, n_b, data);
	quick_sort(data, n_b);
	quick_sort(data, chunk_size - n_b);
}

void	quick_sort_init(t_data *data)
{
	if (check_if_sorted(data->stack[S_A], data->stack[S_A].size))
		return ;
	if (data->stack[S_A].size < SMALL_LIMIT)
	{
		selection_sort_small(data, S_A, data->stack[S_A].size);
		exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
	}
	else if (data->stack[S_A].size < MEDIUM_LIMIT)
		selection_sort_medium(data);
	else
		quick_sort(data, data->stack[S_A].size);
}