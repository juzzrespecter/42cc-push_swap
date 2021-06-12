#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	parse_element(1, 0, argv);
	data = init_data(argv);
	sort_start(&data);
	print_instr_loop(&data);
	return (EXIT_SUCCESS);
}
