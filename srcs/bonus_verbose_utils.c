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

static void	print_stack(int i, t_print_info *purse,  t_stack stack_s, int c_flag)
{
	int	n;
	int	count;
	char	*n_str;
	int	n_len;
	static char	*color_set[] = {
		"\033[52m",
		"\033[53m",
		"\033[54m",
		"\033[55m",
		"\033[56m",
		"\033[57m",
		"\033[0m"
	};

	count = 0;
	n_len = 0;
	n = stack_element(stack_s, i - (purse->height - stack_s.size));
	if (n > 0)
		ft_putchar(' ');
	if (purse->height - (i + 1) < stack_s.size)
	{
		n_str = ft_itoa(n);
		if (c_flag)
			ft_putstr(color_set[0]); //test
		ft_putstr(n_str);
		if (c_flag)
			ft_putstr(color_set[6]);
		ft_strlen(n_str);
	}
	while (count + n_len < purse->width_stack)
	{
		ft_putchar(' ');
		count++;
	}
}

void	print_body(int c_flag, t_print_info *purse, t_data *dummy)
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
		tputs(purse->cr, 1, ft_putc);
		i++;
	}
}

void	print_margin(t_print_info *purse)
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
