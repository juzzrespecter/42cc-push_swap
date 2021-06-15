#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	parse_element(1, 0, argv);
	data = stack_data_init(argv);
	sort_start(&data);
	print_instr_loop(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
