#include "push_swap.h"

static void	checker_stack_ko(t_data *data)
{
	ft_putstr("KO\n");
	free_data(data);
	exit(EXIT_SUCCESS);
}

static void	checker_stack_ok(t_data *data)
{
	ft_putstr("OK\n");
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	checker_stack_order(t_data *data)
{
	int	i;

	i = 0;
	if (data->stack[S_B].size != 0 || data->stack[S_A].size == 0)
		checker_stack_ko(data);
	while (i < data->stack[S_A].size)
	{
		if (i > 0 && data->stack[S_A].array[i] > data->stack[S_A].array[i - 1])
			checker_stack_ko(data);
		i++;
	}
	checker_stack_ok(data);
}

void	checker_parse_args(int argc, char **argv)
{
	if (argc < 2)
		err_and_exit(NULL, NULL, E_NOARG);
	parse_element(1, 0, argv);
}
