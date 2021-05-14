#include "push_swap.h"

/*
 * check if stack_a is sorted
 *
 * check if stack_b is empty
 *
 */

static void	check_stack_ko(t_data *data)
{
			ft_putstr("KO\n");
			free_data(data);
			exit(EXIT_SUCCESS);
}

static void	check_stack_ok(t_data *data)
{
	ft_putstr("OK\n");
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	check_stack_order(t_data *data)
{
	int	i;

	i = 0;
	if (data->stack_b->size != 0 || data->stack_a->size == 0)
		check_stack_ko(data);
	while (i < data->stack_a->size)
	{
		if (i > 0 && data->stack_a->stack[i] > data->stack_a->stack[i - 1])
			check_stack_ko(data);
		i++;
	}
	check_stack_ok(data);
}
