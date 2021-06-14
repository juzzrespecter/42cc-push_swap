#include "push_swap.h"

void	insertion_sort(int **stack_table, int stack_size, int index)
{
	int	*aux_node;
	int	i;

	if (index > (stack_size - 2))
		return ;
	aux_node = stack_table[index + 1];
	i = 0;
	while (i < (index + 1) && \
			aux_node[0] < stack_table[(index - i)][0])
	{
		stack_table[(index - i) + 1] = stack_table[(index - i)];
		i++;
	}
	stack_table[(index - i) + 1] = aux_node;
	insertion_sort(stack_table, stack_size, index + 1);
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
	insertion_sort(stack_table, stack_size, 0);
	return (stack_table);
}

void	free_index_table(int **index_table, int table_size)
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
