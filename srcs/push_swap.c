#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_list	*argv_lst;

	(void) argc;
	argv_lst = parse_element_list(argv);
	parse_element_recursive(0, argv_lst, argv_lst);
	data = stack_data_init(argv_lst);
	sort_start(&data);
	print_instr_loop(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
