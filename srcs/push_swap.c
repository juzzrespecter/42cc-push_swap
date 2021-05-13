#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	/* recibe stack a
	 * push_swap se encarga de ordenar el stack con el
	 * minimo uso posible de operaciones.
	 * cada operacion es impresa por stdin
	 * caso de error, imprime mensaje pertinente.
	 */

	err_arg_check(argc, argv);
	data = init_data(argv);
	insertion_sort(&data);
	return (EXIT_SUCCESS);
}
