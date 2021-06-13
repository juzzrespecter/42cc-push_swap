#include "push_swap.h"

static void swap_in_array(int from, int to, int **heap)
{
	int	*swap_aux;

	swap_aux = heap[from - 1];
	heap[from - 1] = heap[to - 1];
	heap[to - 1] = swap_aux;
}

static void	heapify(int index, int heap_limit, int **heap)
{
	int	index_heap[3];

	index_heap[0] = index * 2;
	index_heap[1] = index * 2 + 1;
	index_heap[2] = index;
	if (index_heap[0] <= heap_limit && heap[index_heap[2] - 1][0] < heap[index_heap[0]- 1][0])
		index_heap[2] = index_heap[0];
	if (index_heap[1] <= heap_limit && heap[index_heap[2] - 1][0] < heap[index_heap[1] - 1][0])
		index_heap[2] = index_heap[1];
	if (index_heap[2] == index)
		return ;
	swap_in_array(index, index_heap[2], heap);
	heapify(index_heap[2], heap_limit, heap);
}

int	**heap_sort(int **heap, int heap_size)
{
	int	i;

	//heap = (int *)malloc(heap_size * sizeof(int));
	//ft_memcpy(heap, stack_array + (stack_size - heap_size), heap_size * sizeof(int));
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
		heapify(1, heap_size - (i + 1) , heap);
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

