#include "push_swap.h"

static void	parse_element_duplicates(int start, char **argv)
{
	char	*to_cmp;
	int	i;
	int	j;

	i = 0;
	while (argv[start + i])
	{
		j = 0;
		to_cmp = argv[start + i];
		while (j < i)
		{
			if (!ft_strncmp(to_cmp, argv[start + j], ft_strlen(to_cmp) + 1))
				err_and_exit(NULL, to_cmp, E_DUPL);
			j++;
		}
		i++;
	}
}

static void	parse_element_overflow(char *element)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (*(element + i) == '0')
		i++;
	len = ft_strlen(element + i);
	if (len < 10)
		return ;
	if (len == 10 && ft_strncmp(element + i, "2147483647", len) > 0)
		err_and_exit(NULL, element + i, E_INTOVF);
	if (len == 11 && ft_strncmp(element + i, "-2147483648", len) > 0)
		err_and_exit(NULL, element + i, E_INTOVF);
}

void	parse_element(int i, int stack_size, char **argv)
{
	int	count;

	count = 0;
	if (!argv[i])
	{
		if (!stack_size)
			err_and_exit(NULL, NULL, E_NOARG);
		parse_element_duplicates(i - stack_size, argv);
		return ;
	}
	if (argv[i][count] == '-')
		count++;
	while (argv[i][count]) 
	{
		if (!ft_isdigit(argv[i][count]))
			err_and_exit(NULL, argv[i], E_NONUM);
		count++;
	}
	parse_element_overflow(argv[i]);
	parse_element(i + 1, stack_size + 1, argv);
}

static void	parse_rand(int i, char **argv)
{
	int	count;

	count = 0;
	if (!argv[i])
		print_help_and_exit();
	while (argv[i][count])
	{
		if (!ft_isdigit(argv[i][count]))
			print_help_and_exit();
		count++;
	}
	if (argv[i + 1])
	{
		if (ft_strncmp(argv[i + 1], "BEST_CASE", 10) && ft_strncmp(argv[i + 1], "WORST_CASE", 11))
			print_help_and_exit();
	}
	return ;
}

void	parse_args(int i, char **argv)
{
	if (!argv[i])
		err_and_exit(NULL, NULL, E_NOARG);
	if (!ft_strncmp(argv[i], "-h", 3))
	   print_help_and_exit();
	if (!ft_strncmp(argv[i], "-r", 3))
	{
		parse_rand(i + 1, argv);
		return ;
	}
	if (!ft_strncmp(argv[i], "-v", 3) || !ft_strncmp(argv[i], "-s", 3))
		parse_args(i + 1, argv);
	else
		parse_element(i, 0, argv);
}
