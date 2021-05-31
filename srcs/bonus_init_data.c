#include "bonus_push_swap.h"

static int	init_flags(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_strncmp("-v", argv[i], 3))
			data->flags[V_FLAG] = 1;
		else if (!ft_strncmp("-r", argv[i], 3))
			data->flags[R_FLAG] = 1;
		else if (!ft_strncmp("-c", argv[i], 3))
			data->flags[C_FLAG] = 1;
		else
			return (i);
		i++;
	}
	return (i);
}

static t_stack	flag_manager(char **argv, t_data *data)
{
	int		argv_start;
	t_stack	stack;

	argv_start = init_flags(argv, data);
	if (data->flags[R_FLAG])
		stack = fill_stack_with_rand(argv_start, argv);
	else
		stack = fill_stack(argv_start, argv);
	if (data->flags[V_FLAG])
		data->bonus_misc = (void *)init_bonus_table(stack, data);
	return (stack);
}

t_data	init_data_with_flags(char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.stack[S_A] = flag_manager(argv, &data);
	data.stack[S_B].array = (int *)malloc(sizeof(int) * data.stack[S_A].size);
	if (!data.stack[S_B].array || !data.stack[S_A].array)
		err_and_exit(&data, NULL, E_NOMEM);
	return (data);
}
