#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	/* recibe stack a
	 * push_swap se encarga de ordenar el stack con el
	 * minimo uso posible de operaciones.
	 * cada operacion es impresa por stdin
	 * caso de error, imprime mensaje pertinente.
	 */

	parse_args(1, argv);
	data = init_data(argv);
//	insertion_sort(&data);
	heap_sort(&data);
	//selection_sort(&data);
	return (EXIT_SUCCESS);
}
