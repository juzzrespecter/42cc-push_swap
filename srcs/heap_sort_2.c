#include "push_swap.h"
#include <stdio.h>

static int	n_of_recursions(int leaf, t_stack heap)
{
	int	i;
	int	n;
	int	parent;

	i = (heap.size + 1) / 2;
	n = 0;
	parent = heap.array[i - 1];
	while (leaf > parent && i > 0)
	{
		i = i / 2;
		parent = heap.array[i - 1];
		n++;
	}
	return (n);
}

static void	heapify(int i, int n, t_data *data)
{
	if (n == 0 || data->stack_b.size == 0)
	{
		exec_cmd("rra", 1, data);
		exec_cmd("pb", 1, data);
		return ;
	}
	exec_cmd("rb", i, data);
	exec_cmd("pa", 1, data);
	heapify(i / 2, n - 1, data);
	exec_cmd("rrb", i, data);
	exec_cmd("pb", 1, data);
}

void	heap_sort(t_data *data)
{
	int	count[2];
	int	size;
	int	leaf;
	int	n;

	size = data->stack_a.size;
	ft_bzero(count, 2 * sizeof(int));
	while (count[0] < size)
	{
		leaf = data->stack_a.array[index_pos(data->stack_a, 0)];
		n = n_of_recursions(leaf, data->stack_b);
		exec_cmd("ra", 1, data);
		heapify((data->stack_b.size + 1) / 2, n, data);
		count[0]++;
	}
	while (count[1] < size)
	{
		if (data->stack_b.size == 0)
			return ;
		exec_cmd("rrb", 1, data);
		exec_cmd("pa", 2, data);
		leaf = data->stack_a.array[index_pos(data->stack_a, 0)];
		n = n_of_recursions(leaf, data->stack_b);
		heapify((data->stack_b.size + 1) / 2, n, data);
		count[1]++;
	}
}
