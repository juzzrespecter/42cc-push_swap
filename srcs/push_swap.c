#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	parse_args(1, argv);
	data = init_data(argv);
//	insertion_sort(&data);
	quick_sort(data.stack[S_A].size, &data);
	return (EXIT_SUCCESS);
}
