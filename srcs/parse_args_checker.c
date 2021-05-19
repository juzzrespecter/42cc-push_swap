#include "push_swap.h"

void	parse_args_checker(int argc, char **argv)
{
	if (argc < 2)
		err_and_exit(NULL, NULL, E_NOARG);
	parse_element(1, 0, argv);
}
