#include <stdio.h>
#include <stdlib.h>

void	print_array(int **array_table)
{
	int index = 0;

	while (index < 10)
	{
		printf("(%d, %d)\n",\
				array_table[index][0],\
				array_table[index][1]);
		index++;
	}
}

void	insertion_sort(int **array_table, int index)
{
	int	*aux_node;
	int	i;

	if (index > 9)
		return ;
	aux_node = array_table[index + 1];
	i = 0;
	while (i < (index + 1) && \
		       array_table[(index - i) + 1][0] < array_table[(index - i)][0])
	{
		array_table[(index - i) + 1] = array_table[(index - i)];
		i++;
	}
	array_table[(index - i) + 1] = aux_node;
	insertion_sort(array_table, index + 1);
}

int	insertion_test(int array[])
{
	int	**array_table;
	int	*content;
	int	index = 0;

	array_table = (int **)malloc(sizeof(int *) * 10);
	while (index < 10)
	{
		content = (int *)malloc(sizeof(int) * 2);
		content[0] = array[index];
		content[1] = index;
		array_table[index] = content;
		index++;
	}
	print_array(array_table);
	insertion_sort(array_table, 0);
	print_array(array_table);
	return (0);
}

int	main()
{
	int	array[] = {
		53, 2, 3, 6, 4,
		9, -1, 0, 8, 24
	};
	insertion_test(array);
}
