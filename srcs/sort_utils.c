#include "push_swap.h"

int	find_smallest_number(t_stack stack,  int pass)
{
	int	i;
	int	smallest;
	int	smallest_pos;

	i = 0;
	smallest = stack_ud(stack, 0);
	smallest_pos = 0;
	while (i < pass)
	{
		if (smallest > stack_ud(stack, i))
		{
			smallest_pos = i;
			smallest = stack_ud(stack, i);
		}
		i++;
	}
	return (smallest_pos);
}

int	find_biggest_number(t_stack stack,  int pass)
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_ud(stack, 0);
	biggest_pos = 0;
	while (i < pass)
	{
		if (biggest < stack_ud(stack, i))
		{
			biggest_pos = i;
			biggest = stack_ud(stack, i);
		}
		i++;
	}
	return (biggest_pos);
}

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

