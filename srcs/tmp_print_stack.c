#include "push_swap.h"
#include <stdio.h>

void	printf_stack(t_stack *stack_a, t_stack *stack_b)
{
	int	i;

	i = 0;
	printf("actual size: a(%d) b(%d)\n", stack_a->size, stack_b->size);
	while (i < stack_a->size || i < stack_b->size)
	{
		if (i < stack_a->size)
			printf("%d", stack_a->array[stack_a->size - i - 1]);
		else 
			printf(" ");
		if (i < stack_b->size)
			printf("    %d\n", stack_b->array[stack_b->size - i - 1]);
		else
			printf("\n");
		i++;
	}
}
