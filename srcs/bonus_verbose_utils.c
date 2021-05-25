#include "bonus_push_swap.h"

static void	print_padding(int padding, int neg)
{
	int	i;

	i = 0;
	while (i + neg < padding)
	{
		ft_putchar(' ');
		i++;
	}
}

static void	print_stack(int i, int n, t_print_info *purse,  t_stack stack_s)
{
	int	count;
	int	written;
	char	*element;

	count = 0;
	written = 0;
	if (purse->height - (i + 1) < stack_s.size)
	{
		element = ft_itoa(n);
		ft_putstr(element);
		written = ft_strlen(element);
	}
	written -= (n < 0);
	while (count + written < purse->width_stack)
	{
		ft_putchar(' ');
		count++;
	}
}

void	print_body(t_print_info *purse)
{
	int	i;
	int	n;

	i = 0;
	while (i < purse->height)
	{
		ft_putstr(purse->left_margin);
		ft_putchar(purse->wall);
		n = stack_element(purse->stack_aux[S_A], i - (purse->height - purse->stack_aux[S_A].size));
		print_padding(purse->padding, (n < 0));
		print_stack(i, n, purse, purse->stack_aux[S_A]);
		ft_putstr(" | ");
		n = stack_element(purse->stack_aux[S_B], i - (purse->height - purse->stack_aux[S_B].size));
		print_stack(i, n, purse, purse->stack_aux[S_B]);
		print_padding(purse->padding, (n < 0));
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
