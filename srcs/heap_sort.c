#include "push_swap.h"

static void	swap_in_array(int from, int to, int **heap)
{
	int	*swap_aux;

	swap_aux = heap[from - 1];
	heap[from - 1] = heap[to - 1];
	heap[to - 1] = swap_aux;
}

static void	heapify(int index, int heap_limit, int **heap)
{
	int	h_index[3];

	h_index[0] = index * 2;
	h_index[1] = index * 2 + 1;
	h_index[2] = index;
	if (h_index[0] <= heap_limit && heap[h_index[2] - 1][0] < heap[h_index[0] - 1][0])
		h_index[2] = h_index[0];
	if (h_index[1] <= heap_limit && heap[h_index[2] - 1][0] < heap[h_index[1] - 1][0])
		h_index[2] = h_index[1];
	if (h_index[2] == index)
		return ;
	swap_in_array(index, h_index[2], heap);
	heapify(h_index[2], heap_limit, heap);
}

int	**heap_sort(int **heap, int heap_size)
{
	int	i;

	i = 0;
	while (i < heap_size / 2)
	{
		heapify((heap_size / 2) - i, heap_size, heap);
		i++;
	}
	i = 0;
	while (i < heap_size)
	{
		swap_in_array(1, heap_size - i, heap);
		heapify(1, heap_size - (i + 1), heap);
		i++;
	}
	return (heap);
}

int	**get_index_table(int *array, int stack_size)
{
	int	**stack_table;
	int	*content;
	int	index;

	index = 0;
	stack_table = (int **)malloc(sizeof(int *) * stack_size);
	while (index < stack_size)
	{
		content = (int *)malloc(sizeof(int) * 2);
		content[0] = array[stack_size - (index + 1)];
		content[1] = index;
		stack_table[index] = content;
		index++;
	}
	stack_table = heap_sort(stack_table, stack_size);
	return (stack_table);
}

void	free_table(int **index_table, int table_size)
{
	int	i;

	i = 0;
	while (i < table_size)
	{
		free(index_table[i]);
		i++;
	}
	free(index_table);
}
