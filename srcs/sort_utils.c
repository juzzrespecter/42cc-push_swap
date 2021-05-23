#include "push_swap.h"

int	stack_element(t_stack stack_s, int pos)
{
	return (stack_s.array[stack_s.size - (pos + 1)]);
}

void	print_instr(int instr_i, int fd)
{
	static char	*instr_array[11] = {
		"sa: swapped the first two elements in stack a\n",
		"sb: swapped the first two elements in stack b\n",
		"ss: swapped the first two elements in stack a and stack b\n",
		"pa: pushed the first element of stack b into stack a\n",
		"pb: pushed the first element of stack a in stack b\n",
		"ra: rotated stack a\n",
		"rb: rotated stack b\n",
		"rr: rotated stack a and stack b\n",
		"rra: reverse rotated stack a\n",
		"rrb: reverse rotated stack b\n",
		"rrr: reverse rotated stack a and stack b\n"
	};

	ft_putstr_fd(data->purse.left_margin, data->save_fd);
	ft_putstr_fd(instr_array[instr_i], fd);
}

void	exec_instr_loop(int instr_id, int stack_id, int n, t_data *data)
{
	int	i;
	static void (*instr_table[])(int, t_data) = {
		swap,
		push,
		rotate,
		rev_rotate
	}

	i = 0;
	while (i < n)
	{
		instr_table[instr_id](stack_id, data);
		save_instr(instr, data);
		if (data->flags[V_FLAG])
			print_verbose(instr_id, data);
		if (data->flags[S_FLAG])
			print_instr(instr, data->save_fd);
		i++;
	}
}
