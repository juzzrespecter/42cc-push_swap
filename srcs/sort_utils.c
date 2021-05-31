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
