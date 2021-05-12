#include "push_swap.h"
#include <stdio.h>

void	printf_stack(t_stack *stack, int size_b)
{
	int	i;

	i = 0;
	printf("actual size: a(%d) b(%d)\n", stack->size, size_b);
	while (i < stack->size)
	{
		printf("- %d\n", stack->stack[stack->size - i - 1]);
		i++;
	}
}
