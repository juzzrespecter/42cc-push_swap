#include "push_swap.h"

t_data	stack_data_init(char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.stack[STACK_ID_A] = stack_fill(1, argv);
	data.stack[STACK_ID_B].array = (int *)malloc(sizeof(int) *\
		   	data.stack[STACK_ID_A].size);
	if (!data.stack[STACK_ID_B].array || !data.stack[STACK_ID_A].array)
		err_and_exit(&data, NULL, E_NOMEM);
	ft_bzero(&data.instr_set, sizeof(t_instr));
//	data.n_steps = (data.stack[STACK_ID_A].size / 100) + 6;
//	data.n_ins = (data.stack[STACK_ID_A].size / 300) + 2;
	data.n_steps = (data.stack[STACK_ID_A].size < 101) ? 7 : 13;
	data.n_ins = (data.stack[STACK_ID_A].size < 101) ? 2 : 3;
	return (data);
}
