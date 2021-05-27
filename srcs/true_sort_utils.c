#include "push_swap.h"

void	check_already_sorted(t_stack stack, t_data *data)
{
	int	i;

	i = 0;
	while ((i + 1) < stack.size)
	{
		if (stack.array[stack.size - i] > stack.array[stack.size - (i + 1)])
			return ;
		i++;
	}
	free_data(data); // check exit
	exit(EXIT_SUCCESS);
}

void	small_sort(t_data *data)
{
	// 1. choose pivot
	// 2. mueve (n < pivot) a stack b
	// 3. busca primer desorden en cada stack (i, j)
	// 4. mueve a primer desorden: (ra, rra) & (rb, rrb)
	// 5. a: (n[i] > n[i + 1] -> sa) b: (n[j] < n[j + 1] -> sb) hasta recorrer todo el stack (checkthis)
	// comprueba orden: OK -> exit, KO -> 4.
	// 6. OK -> pa * stack_b.size
	//
	// basicamente: 1 paso de quick sort, bubble sort a los dos stacks
}
