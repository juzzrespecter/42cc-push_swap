#include "push_swap.h"

static int	instr_array_index(char *instr)
{
	if (!ft_strncmp(instr, "sa", 3))
		return (0);
	if (!ft_strncmp(instr, "sb", 3))
		return (1);
	if (!ft_strncmp(instr, "ss", 3))
		return (2);
	if (!ft_strncmp(instr, "pa", 3))
		return (3);
	if (!ft_strncmp(instr, "pb", 3))
		return (4);
	if (!ft_strncmp(instr, "ra", 3))
		return (5);
	if (!ft_strncmp(instr, "rb", 3))
		return (6);
	if (!ft_strncmp(instr, "rr", 3))
		return (7);
	if (!ft_strncmp(instr, "rra", 4))
		return (8);
	if (!ft_strncmp(instr, "rrb", 4))
		return (9);
	return (10);
}

int	index_pos(t_stack stack_s, int pos)
{
	return (stack_s.size - (pos + 1));
}

void	print_instr(char *instr, int fd)
{
	char	*instr_array[11];

	instr_array[0] = ": swapped the first two elements in stack a\n";
	instr_array[1] = ": swapped the first two elements in stack b\n";
	instr_array[2] = ": swapped the first two elements in stack a and stack b\n";
	instr_array[3] = ": pushed the first element of stack b into stack a\n";
	instr_array[4] = ": pushed the first element of stack a in stack b\n";
	instr_array[5] = ": rotated stack a\n";
	instr_array[6] = ": rotated stack b\n";
	instr_array[7] = ": rotated stack a and stack b\n";
	instr_array[8] = ": reverse rotated stack a\n";
	instr_array[9] = ": reverse rotated stack b\n";
	instr_array[10] = ": reverse rotated stack a and stack b\n";
	ft_putstr_fd(instr, fd);
	ft_putstr_fd(instr_array[instr_array_index(instr)], fd);
}

void	exec_cmd(char *instr, int n, t_data *data)
{
	int	i;

	i = 0;
	while (i < n)
	{
		cmp_instr_list(instr, data);
		save_instr(instr, data);
		if (data->flags[V_FLAG])
			print_cmd(instr, data);
		if (data->flags[S_FLAG])
		{
			ft_putstr_fd(data->purse.left_margin, data->save_fd);
			print_instr(instr, data->save_fd);
		}
		i++;
	}
}
