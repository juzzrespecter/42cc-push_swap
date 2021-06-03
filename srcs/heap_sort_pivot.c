#include "push_swap.h"

static void swap_in_array(int from, int to, int *heap)
{
	int	swap_aux;

	swap_aux = heap[from - 1];
	heap[from - 1] = heap[to - 1];
	heap[to - 1] = swap_aux;
}

static void	heapify(int index, int heap_limit, int *heap)
{
	int	index_heap[3];

	index_heap[0] = index * 2;
	index_heap[1] = index * 2 + 1;
	index_heap[2] = index;
	if (index_heap[0] <= heap_limit && heap[index_heap[2] - 1] < heap[index_heap[0] - 1])
		index_heap[2] = index_heap[0];
	if (index_heap[1] <= heap_limit && heap[index_heap[2] - 1] < heap[index_heap[1] - 1])
		index_heap[2] = index_heap[1];
	if (index_heap[2] == index)
		return ;
	swap_in_array(index, index_heap[2], heap);
	heapify(index_heap[2], heap_limit, heap);
}

int	*heap_sort(int *stack_array, int stack_size, int chunk_size)
{
	int	*heap;
	int	i;

	heap = (int *)malloc(chunk_size * sizeof(int));
	ft_memcpy(heap, stack_array + (stack_size - chunk_size), chunk_size * sizeof(int));
	i = 0;
	while (i < chunk_size / 2)
	{
		heapify((chunk_size / 2) - i, chunk_size, heap);
		i++;
	}
	i = 0;
	while (i < chunk_size)
	{
		swap_in_array(1, chunk_size - i, heap);
		heapify(1, chunk_size - (i + 1) , heap);
		i++;
	}
	return (heap);
}
