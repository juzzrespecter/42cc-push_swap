#include "bonus_push_swap.h"
#include <stdio.h>

static void	print_padding(int padding)
{
	int	i;

	i = 0;
	while ((i + 1) < padding)
	{
		ft_putchar(' ');
		i++;
	}
}

static char	*print_stack_color(long n, long r_max, long r_min)
{
	static char	*color_set[] = {
		"\x1b[32m",
		"\x1b[92m",
		"\x1b[93m",
		"\x1b[33m",
		"\x1b[91m",
		"\x1b[31m"
	};
	long n_long;
	double index;

	n_long = n - r_min;
	index = n_long / (double)(r_max - r_min);
	index = index * 5;
	return (color_set[(int)index]);
}	

static void	print_stack(int i, t_bonus_table *b_table,  t_stack stack_s, int c_flag)
{
	int	n;
	int	count;
	char	*n_str;
	int	n_len;
	int neg;

	count = 0;
	n_len = 0;
	neg = 0;
	n = stack_element(stack_s, i - (b_table->height - stack_s.size));
	if (n < 0)
		neg = 1;
	if (!neg)
		ft_putchar(' ');
	if (b_table->height - (i + 1) < stack_s.size)
	{
		n_str = ft_itoa(n);
		if (c_flag)
			ft_putstr(print_stack_color(n, b_table->r_max, b_table->r_min)); //test
		ft_putstr(n_str);
		if (c_flag)
			ft_putstr("\x1b[0m"); //test
		n_len = ft_strlen(n_str);
		free(n_str);
	}
	while (count + n_len < b_table->width_stack + neg)
	{
		ft_putchar(' ');
		count++;
	}
}

void	print_body(int c_flag, t_bonus_table *b_table, t_data *dummy)
{
	int	i;

	i = 0;
	while (i < b_table->height)
	{
		ft_putstr(b_table->left_margin);
		ft_putchar(b_table->wall);
		print_padding(b_table->padding);
		print_stack(i, b_table, dummy->stack[S_A], c_flag);
		ft_putstr(" | ");
		print_stack(i, b_table, dummy->stack[S_B], c_flag);
		print_padding(b_table->padding);
		ft_putchar(b_table->wall);
		ft_putchar('\n');
		i++;
	}
}

void	print_margin(t_bonus_table *b_table)
{
	int	i;

	i = 0;
	ft_putstr(b_table->left_margin);
	while (i < b_table->width)
	{
		ft_putchar(b_table->margin);
		i++;
	}
	ft_putstr("\n");
}
