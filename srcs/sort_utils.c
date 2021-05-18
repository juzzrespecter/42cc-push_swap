#include "push_swap.h"

int	index_pos(t_stack stack_s, int pos)
{
	return (stack_s.size - (pos + 1));
}

void	exec_cmd(char *cmd, int n, t_data *data)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmp_instr_list(cmd, data);
		ft_putstr_fd(cmd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		if (data->flags[V_FLAG])
			print_cmd(cmd, data);
		/* if (data->flags[V_FLAG])
		 * 		save_cmd(cmd, data) */
		i++;
	}
}
