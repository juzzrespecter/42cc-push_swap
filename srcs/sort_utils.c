#include "push_swap.h"

int	check_if_sorted(t_stack stack, int pass)
{
	int	i;

	i = 0;
	while ((i + 1) < pass)
	{
		if (stack_ud(stack, i) > stack_ud(stack, i + 1))
			return (0);
		i++;
	}
	return (1);
}

int	find_next_up(double pivot, int pass, t_stack stack)
{
	int	pos;

	pos = 0;
	if (pass < 1)
		return (-1);
	while (pos < pass)
	{
		if (stack_ud(stack, pos) < pivot)
			return (pos);
		pos++;
	}
	return (-1);
}

int	find_biggest_number(t_stack stack, int pass)
{
	int stack_aux;
	int	index;
	int i;

	i = 0;
	stack_aux = stack_ud(stack, 0);
	index = 0;
	while (i < pass)
	{
		stack_aux = stack_ud(stack, i);
		if (stack_aux > stack_ud(stack, index))
			index = i;
		i++;
	}
	return (index);
}

int	find_smallest_number(t_stack stack, int pass)
{
	int stack_aux;
	int	index;
	int i;

	stack_aux = stack_ud(stack, 0);
	index = 0;
	i = 0;
	while (i < pass)
	{
		stack_aux = stack_ud(stack, i);
		if (stack_aux < stack_ud(stack, index))
			index = i;
		i++;
	}
	return (index);
}
