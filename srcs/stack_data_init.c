#include "push_swap.h"

t_data	stack_data_init(char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.stack[STACK_ID_A] = stack_fill(1, argv);
	data.stack[STACK_ID_B].array = (int *)malloc(sizeof(int) \
			* data.stack[STACK_ID_A].size);
	if (!data.stack[STACK_ID_B].array || !data.stack[STACK_ID_A].array)
		err_and_exit(&data, NULL, E_NOMEM);
	data.n_steps = 7 + (data.stack[STACK_ID_A].size / 100);
	data.n_ins = 1 + (data.stack[STACK_ID_A].size / 100);
	return (data);
}
