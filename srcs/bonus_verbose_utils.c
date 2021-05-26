#include "bonus_push_swap.h"

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

#include <stdio.h>

static char	*print_stack_color(int n)
{
	static char	*color_set[] = {
		"\x1b[31m",
		"\x1b[91m",
		"\x1b[33m",
		"\x1b[93m",
		"\x1b[92m",
		"\x1b[32m"
	};
	long index;
	long aux = INT_MAX;

	index = (long)n + aux;
	index /= (aux * 2) / 6L;
	return (color_set[index]);
}	

static void	print_stack(int i, t_bonus_table *purse,  t_stack stack_s, int c_flag)
{
	int	n;
	int	count;
	char	*n_str;
	int	n_len;
	int neg;

	count = 0;
	n_len = 0;
	neg = 0;
	n = stack_element(stack_s, i - (purse->height - stack_s.size));
	if (n < 0)
		neg = 1;
	if (!neg)
		ft_putchar(' ');
	if (purse->height - (i + 1) < stack_s.size)
	{
		n_str = ft_itoa(n);
		if (c_flag)
			ft_putstr(print_stack_color(n)); //test
		ft_putstr(n_str);
		if (c_flag)
			ft_putstr("\x1b[0m"); //test
		n_len = ft_strlen(n_str);
		free(n_str);
	}
	while (count + n_len < purse->width_stack + neg)
	{
		ft_putchar(' ');
		count++;
	}
}

void	print_body(int c_flag, t_bonus_table *purse, t_data *dummy)
{
	int	i;

	i = 0;
	while (i < purse->height)
	{
		ft_putstr(purse->left_margin);
		ft_putchar(purse->wall);
		print_padding(purse->padding);
		print_stack(i, purse, dummy->stack[S_A], c_flag);
		ft_putstr(" | ");
		print_stack(i, purse, dummy->stack[S_B], c_flag);
		print_padding(purse->padding);
		ft_putchar(purse->wall);
		ft_putchar('\n');
		tputs(tgetstr("cr", NULL), 1, ft_putc);
		i++;
	}
}

void	print_margin(t_bonus_table *purse)
{
	int	i;

	i = 0;
	ft_putstr(purse->left_margin);
	while (i < purse->width)
	{
		ft_putchar(purse->margin);
		i++;
	}
	ft_putstr("\n");
}
