#include "bonus_push_swap.h"

static void	parse_rand(int i, char **argv)
{
	int	count;

	count = 0;
	if (!argv[i])
		err_and_exit(NULL, NULL, E_NORAND);
	while (argv[i][count])
	{
		if (!ft_isdigit(argv[i][count]))
			err_and_exit(NULL, NULL, E_NORAND);
		count++;
	}
	if (argv[i + 1])
	{
		if (ft_strncmp(argv[i + 1], "BEST_CASE", 10) && \
			   ft_strncmp(argv[i + 1], "WORST_CASE", 11))
			err_and_exit(NULL, NULL, E_NORAND);
	}
	return ;
}

static void	parse_args(int i, char **argv)
{
	if (!argv[i])
		err_and_exit(NULL, NULL, E_NOARG);
	if (!ft_strncmp(argv[i], "-r", 3))
	{
		parse_rand(i + 1, argv);
		return ;
	}
	if (!ft_strncmp(argv[i], "-v", 3) || !ft_strncmp(argv[i], "-c", 3))
		parse_args(i + 1, argv);
	else
		parse_element(i, 0, argv);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	parse_args(1, argv);
	data = init_data_with_flags(argv);
	quick_sort_init(&data);
	if (data.flags[V_FLAG])
		print_visualizer_init(&data);
	print_instr_loop(&data);
	return (EXIT_SUCCESS);
}
