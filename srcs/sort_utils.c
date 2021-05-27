#include "push_swap.h"

int	check_already_sorted(t_stack stack, int rec)
{
	int	i;

	i = 0;
	if (rec == 1)
		return (1);
	while ((i + 1) < rec)
	{
		if (stack.array[stack.size - (i + 1)] > stack.array[stack.size - (i + 2)])
			return (0);
		i++;
	}
	return (1);
}

void	small_sort(t_data *data)
{
	(void) data;
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
