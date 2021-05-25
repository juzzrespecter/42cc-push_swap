#include "push_swap.h"

void	free_data(t_data *data)
{
	if (data->stack[S_A].array)
		free(data->stack[S_A].array);
	if (data->stack[S_B].array)
		free(data->stack[S_B].array);
	if (data->instr_list_head)
		ft_lstclear(&data->instr_list_head, &free);
}

void	err_and_exit(t_data *data, char *err_token, int err_code)
{
	static char	*err_descrp[8] = {
		": duplicate argument.\n",
		"No arguments given to the program.\n",
		": not a valid argument.\n",
		": argument overflows integer limits.\n",
		"Not enough memory space on system.\n",
		": unknown flag.\n",
		": not a valid instruction.\n"
		": bad random flag format ( usage = { -r [N_RANGE] ([BEST_CASE | WORST_CASE]) }\n"
	};

	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err_token != NULL)
		ft_putstr_fd(err_token, STDERR_FILENO);
	ft_putstr_fd(err_descrp[err_code], STDERR_FILENO);
	if (err_code == E_NOINSTR)
		free(err_token);
	if (data != NULL)
		free_data(data);
	exit(EXIT_FAILURE);
}
