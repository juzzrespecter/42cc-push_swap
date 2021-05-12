#include "push_swap.h"

/*	implementar gestion de memoria dinamica aqui	*/
/*	meter mensajes de error especificos	*/

void	free_data(t_data *data)
{
	if (data->stack_a)
	{
		free(data->stack_a->stack);
		free(data->stack_a);
	}
	if (data->stack_b)
	{
		free(data->stack_b->stack);
		free(data->stack_b);
	}
	if (data->instr_list_head)
		ft_lstclear(&data->instr_list_head, &free);
}

void	err_and_exit(t_data *data, char *err_token, int err_code)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (err_token != NULL)
		ft_putstr_fd(err_token, STDERR_FILENO);
	if (err_code == E_DUPL)
		ft_putstr_fd(": duplicate argument\n", STDERR_FILENO);
	if (err_code == E_NOARG)
		ft_putstr_fd("No arguments given to the program.\n", STDERR_FILENO);
	if (err_code == E_NONUM)
		ft_putstr_fd(": not a valid argument.\n", STDERR_FILENO);
	if (err_code == E_INTOVF)
		ft_putstr_fd(": argument overflows integer limits.\n", STDERR_FILENO);
	if (err_code == E_NOMEM)
		ft_putstr_fd("Not enough memory space on system\n", STDERR_FILENO);
	if (err_code == E_NOINSTR)
	{
		ft_putstr_fd(": not a valid instruction.\n", STDERR_FILENO);
		free(err_token);
	}
	if (data != NULL)
		free_data(data);
	exit(EXIT_FAILURE);
}

/*
 * 	- argumento duplicado
 * 	- no se ha pasado un argumento
 * 	- argumento no es un numero
 * 	- argumento es superior a un entero
 * 	- enomem
 * 	- instruccion invalida
 */
