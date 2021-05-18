#include "push_swap.h"

void	print_ceiling(t_print_info purse)
{
	int	i;

	i = 0;
	ft_putstr("          ");
	while (i < purse.width)
	{
		ft_putstr("_");
		i++;
	}
	ft_putstr("\n");
}

static void	print_element(int width_stack, int i, t_stack stack_s)
{
	int	elem_len;
	char	*elem;
	int	count;

	/* faltan instrucciones colorizadas */

	elem_len = 0;
	count = 0;
	if (i < stack_s.size)
	{
		elem = ft_itoa(stack_s.array[stack_s.size - (i + 1)]);
		elem_len = ft_strlen(elem);
		ft_putstr(elem);
		free(elem);
	}
	while (elem_len + count < width_stack)
	{
		ft_putchar(' ');
		count++;
	}

}

void	print_walls(t_print_info purse, t_data *data)
{
	int	i;

	i = 0;
	while (i < purse.height)
	{
		ft_putstr("          |  ");
		print_element(purse.width_stack, i, data->stack_a);
		ft_putstr("  $$  ");
		print_element(purse.width_stack, i, data->stack_b);
		ft_putstr("  |\n");
		i++;
	}
}

void	print_cmd_info(char *cmd, t_data *data)
{
/*
 * tmp
 */

	(void) data;
	ft_putstr(cmd);
}
