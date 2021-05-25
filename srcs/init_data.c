#include "push_swap.h"

t_stack	fill_stack(int start, char **argv)
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

t_data	init_data(char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.stack[S_A] = fill_stack(1, argv);
	data.stack[S_B].array = (int *)malloc(sizeof(int) * data.stack[S_A].size);
	if (!data.stack[S_B].array || !data.stack[S_A].array)
		err_and_exit(&data, NULL, E_NOMEM);
	return (data);
}
