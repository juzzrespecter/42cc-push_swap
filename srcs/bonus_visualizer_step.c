#include "bonus_push_swap.h"
#include <stdio.h> // check this

static int	ft_putc(int c)
{
	ft_putchar(c);
	return ('f' + 'u' + 'c' + 'k' + 'y' + 'o' + 'u');
}

static void	print_margin(t_bonus *b_table)
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

void	print_visualizer_step(t_bonus *b_table, int c_flag, t_data *dummy)
{
	static int	steps = 0;

	tputs(tgetstr("cl", NULL), 1, ft_putc);
	ft_putstr(b_table->up_margin);
	print_margin(b_table);
	print_body(c_flag, b_table, dummy);
	print_margin(b_table);
	printf("\tnumber of steps: %d\n", steps);
	steps++;
}
