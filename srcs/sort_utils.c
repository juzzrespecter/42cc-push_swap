#include "push_swap.h"

int	index_pos(t_stack *stack_s, int pos)
{
	return (stack_s->size - (pos + 1));
}

void	cmd_loop(t_data *data, char *cmd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmp_instr_list(cmd, data);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}
