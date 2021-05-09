#include "push_swap.h"

/*	implementar gestion de memoria dinamica aqui	*/

void	free_data(t_checker_data *data)
{
	if (data->stack_a->stack)
		free(data->stack_a->stack);
	if (data->stack_b->stack)
		free(data->stack_b->stack);
	if (data->instr_list_head)
		ft_lstclear(&data->instr_list_head, &free);
}

void	err_and_exit(t_checker_data *data)
{
	free_data(data);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
