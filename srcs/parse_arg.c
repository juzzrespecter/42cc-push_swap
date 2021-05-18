#include "push_swap.h"
#include <stdio.h>

static int	check_int_overflow(char *integer, int size)
{
	int	comp_out;
	int	zero_len;

	zero_len = 0;
	while (integer[zero_len] == '0')
		zero_len++;
	size -= zero_len;
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

static int	parse_rand_flag(char **argv, int arg_pos)
{
	int	i;

	i = 0;
	arg_pos++;
	if (argv[arg_pos] == NULL)
		print_help_and_exit();
	while (argv[arg_pos][i])
	{
		if (!ft_isdigit(argv[arg_pos][i]))
			print_help_and_exit();
		i++;
	}
	arg_pos++;
	if (argv[arg_pos] != NULL)
	{
		if (ft_strncmp(argv[arg_pos], "BEST_CASE", 10) && ft_strncmp(argv[arg_pos], "WORST_CASE", 11))
			print_help_and_exit();
	}
	return (arg_pos++);
}

static int	parse_flags(char **argv)
{
	int	flag_count;

	/* casos random y help */
	flag_count = 0;
	while ((flag_count + 1) < 5)
	{
		if (argv[flag_count + 1][0] != '-' || ft_isdigit(argv[flag_count][1])) /* check cadena vacia */
			return (flag_count + 1);
		if (!ft_strchr("rvhs", argv[flag_count + 1][1]) || argv[flag_count + 1][2] != 0)
			err_and_exit(NULL, argv[flag_count + 1], E_NOFLAG);
		if (argv[flag_count + 1][1] == 'r')
			return (parse_rand_flag(argv, flag_count));
		flag_count++;
	}
	return (flag_count); 
}

void	parse_arg(int argc, char **argv)
{
	int	count;
	int	i;
	
	i = 0;
	if (argc < 2)
		err_and_exit(NULL, NULL, E_NOARG);
	count = parse_flags(argv);
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

/* hacer un parser de verdad	*/
