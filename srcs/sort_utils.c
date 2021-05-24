#include "push_swap.h"

int	stack_element(t_stack stack_s, int pos)
{
	return (stack_s.array[stack_s.size - (pos + 1)]);
}

/*void	print_instr(int instr_i, t_data *data)
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
	ft_putstr_fd(instr_array[instr_i], data->save_fd);
}*/

void	print_instr(int instr_id, int stack_id)
{
	static const char	instr_array[2][3] = {
		{'s', 'p', 'r'},
		{'a', 'b', 'r'}
	};
	
	if (instr_id == 3)
		ft_putstr("rr");
	else
		ft_putchar(instr_array[0][instr_id]);
	ft_putchar(instr_array[1][stack_id]);
	ft_putchar('\n');
}

void	exec_instr_loop(int instr_id, int stack_id, int n, t_data *data)
{
	int	i;
	static void (*instr_table[])(int, t_data *) = {
		swap,
		push,
		rotate,
		rev_rotate
	};

	i = 0;
	while (i < n)
	{
		instr_table[instr_id](stack_id, data);
		print_instr(instr_id, stack_id);
		if (data->flags[V_FLAG])
			print_verbose(instr_id, data);
		if (data->flags[S_FLAG])
			print_instr(instr, data);
		i++;
	}
}
