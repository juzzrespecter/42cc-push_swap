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

static int	check_duplicates(char **argv, int pos)
{
	int	i;

	i = 0;
	while (i < pos)
	{
		if (!ft_strncmp(argv[i], argv[pos], ft_strlen(argv[pos]) + 1))
			return (E_DUPL);
		i++;
	}
	return (0);
}

void	parse_arg(int argc, char **argv)
{
	int	count;
	int	i;
	
	count = 1;
	i = 0;
	if (argc < 2)
		err_and_exit(NULL, NULL, E_NOARG);
	while (argv[count])
	{
		if (argv[count][0] == '-' && argv[count][1] != 0)
			i++;
		while (argv[count][i])
		{
			if (!ft_isdigit(argv[count][i]))
				err_and_exit(NULL, argv[count], E_NONUM);
			i++;
		}
		if (check_duplicates(argv, count) > 0)
			err_and_exit(NULL, argv[count], E_DUPL);
		if (check_int_overflow(argv[count], i) > 0)
			err_and_exit(NULL, argv[count], E_INTOVF);
		i = 0;
		count++;
	}
}

/*
 * 00000009 <--- valido
 * -v, -h, -r, -s
 * if -r: arg[i + 1] == num, arg[i + 2] puede ser BEST_CASE o WORST_CASE
 *
 *
 */
