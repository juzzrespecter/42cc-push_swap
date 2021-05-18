#include "push_swap.h"

static int	init_flags(char **argv, t_data *data)
{
	int	i;
	
	i = 1;
	while (i < 5)
	{
		if (!ft_strncmp("-v", argv[i + 1], 3))
			data->flags[V_FLAG] = 1;
		else if (!ft_strncmp("-r", argv[i + 1], 3))
			data->flags[R_FLAG] = 1;
		else if (!ft_strncmp("-h", argv[i + 1], 3))
			data->flags[H_FLAG] = 1;
		else if (!ft_strncmp("-s", argv[i + 1], 3))
			data->flags[S_FLAG] = 1;
		else
			return (i);
		i++;
	}
	return (i);
}

static t_stack	fill_stack(int start, char **argv)
{
	t_stack	stack_s;
	int	i;

	stack_s.size = 0;
	i = 0;
	while (argv[start + stack_s.size])
		stack_s.size++;
	stack_s.array = (int *)malloc(sizeof(int) * stack_s.size);
	if (stack_s.array == NULL)
		err_and_exit(NULL, NULL, E_NOMEM);
	while (argv[start + i + 1])
	{
		stack_s.array[stack_s.size - i - 1] = ft_atoi(argv[start + i]);
		i++;
	}
	return (stack_s);
}

static t_stack	flag_manager(char **argv, t_data *data)
{
	int	argv_start;
	t_stack	stack_a;

	argv_start = init_flags(argv, data);
	if (data->flags[H_FLAG])
		print_help_and_exit();
	if (data->flags[R_FLAG])
		stack_a = fill_stack_with_rand(argv_start, argv);
	else
		stack_a = fill_stack(argv_start, argv);
	if (data->flags[V_FLAG])
		data->purse = init_print_cmd(stack_a);
	return (stack_a);
}

t_data	init_data(char **argv)
{
	t_data	data;

	ft_bzero(data.flags, sizeof(int) * 4);
	data.stack_a = flag_manager(argv, &data);
	data.stack_b.array = (int *)ft_calloc(sizeof(int), data.stack_a.size);
	data.stack_b.size = 0;
	data.instr_list_head = NULL;
	if (!data.stack_b.array || !data.stack_a.array)
		err_and_exit(&data, NULL, E_NOMEM);
	return (data);
}
