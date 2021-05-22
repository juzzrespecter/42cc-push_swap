#include "push_swap.h"

static void	print_padding(int padding, int neg)
{
	int	i;

	i = 0;
	while (i + neg < padding)
	{
		ft_putchar(' ');
		i++;
	}
}

#include <stdio.h>

static void	print_stack(int i, int index, t_print_info purse,  t_stack stack_s)
{
	int	count;
	int	written;
	char	*element;

	count = 0;
	written = 0;
	//printf("index: %d, i: %d, height: %d, stack: %d\n", index,i,purse.height,stack_s.size);
	if (purse.height - (i + 1) < stack_s.size)
	{
		element = ft_itoa(stack_s.array[index]);
		ft_putstr(element);
		written = ft_strlen(element);
	}
	written -= (stack_s.array[index] < 0);
	while (count + written < purse.width_stack)
	{
		ft_putchar(' ');
		count++;
	}
}

void	print_body(t_print_info purse, t_data *data)
{
	int	i;
	int	index;
	t_stack stack_a;
	t_stack stack_b;

	i = 0;
	stack_a = data->stack_a;
	stack_b = data->stack_b;
	while (i < purse.height)
	{
		ft_putstr(purse.left_margin);
		ft_putchar(purse.wall);
		index = index_pos(stack_a, i - (purse.height - stack_a.size));
		print_padding(purse.padding, (stack_a.array[index] < 0));
		print_stack(i, index, purse, stack_a);
		ft_putstr(" | ");
		index = index_pos(stack_b, i - (purse.height - stack_b.size));
		print_stack(i, index, purse, stack_b);
		print_padding(purse.padding, (stack_b.array[index] < 0));
		ft_putchar(purse.wall);
		ft_putchar('\n');
		i++;
	}
}

void	print_margin(t_print_info purse)
{
	int	i;

	i = 0;
	ft_putstr(purse.left_margin);
	while (i < purse.width)
	{
		ft_putchar(purse.margin);
		i++;
	}
	ft_putstr("\n");
}
