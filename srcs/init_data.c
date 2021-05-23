#include "push_swap.h"

static int	init_flags(char **argv, t_data *data) // no
{
	int	i;
	
	i = 1;
	while (argv[i])
	{
		if (!ft_strncmp("-v", argv[i], 3))
			data->flags[V_FLAG] = 1;
		else if (!ft_strncmp("-r", argv[i], 3))
			data->flags[R_FLAG] = 1;
		else if (!ft_strncmp("-s", argv[i], 3))
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
	while (argv[start + i])
	{
		stack_s.array[stack_s.size - i - 1] = ft_atoi(argv[start + i]);
		i++;
	}
	return (stack_s);
}

static t_stack	flag_manager(char **argv, t_data *data)
{
	int	argv_start;
	t_stack	stack[S_A];

	argv_start = init_flags(argv, data);
	if (data->flags[R_FLAG])
		stack[S_A] = fill_stack_with_rand(argv_start, argv);
	else
		stack[S_A] = fill_stack(argv_start, argv);
	if (data->flags[V_FLAG])
		data->purse = init_print_cmd(stack[S_A]);
	return (stack[S_A]);
}

t_data	init_data(char **argv)
{
	t_data	data;

	data.filename = "save.txt";
	ft_bzero(data.flags, sizeof(int) * 4);
	data.stack[S_A] = flag_manager(argv, &data);
	data.stack[S_A].array = (int *)ft_calloc(sizeof(int), data.stack[S_A].size);
	data.stack[S_B].size = 0;
	data.instr_list_head = NULL;
	if (!data.stack[S_B].array || !data.stack[S_A].array)
		err_and_exit(&data, NULL, E_NOMEM);
	if (data.flags[S_FLAG])
		data.save_fd = init_savefile(data.filename);
	return (data);
}
