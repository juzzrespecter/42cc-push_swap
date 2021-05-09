#include "push_swap.h"

static int	check_int_overflow(char *integer, int size)
{
	int	comp_out;

	if (size < 10)
		return (0);
	if (size == 10)
	{
		comp_out = ft_strncmp(integer, "2147483647", size);
		return (comp_out);
	}
	if (size == 11)
	{
		comp_out = ft_strncmp(integer, "-2147483648", size);
		return (comp_out);
	}
	return (1);
}

void	err_arg_check(int argc, char **argv)
{
	int	count;
	int	i;
	
	count = 1;
	i = 0;
	if (argc < 2)
		err_and_exit(NULL);
	while (argv[count])
	{
		if (argv[count][0] == '-' && argv[count][1] != 0)
			i++;
		while (argv[count][i])
		{
			if (!ft_isdigit(argv[count][i]))
				err_and_exit(NULL);
			i++;
		}
		if (check_int_overflow(argv[count], i) > 0)
			err_and_exit(NULL);
		i = 0;
		count++;
	}
}
