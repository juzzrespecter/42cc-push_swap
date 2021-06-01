#include "push_swap.h"

static void	print_instr(int instr_id, int stack_id)
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

void	print_instr_loop(t_data *data)
{
	t_list	*instr_n;
	int	*ids;

	instr_n = data->instr_list_head;
	while (instr_n)
	{
		ids = (int *)instr_n->content;
		print_instr(ids[0], ids[1]);
		instr_n = instr_n->next;
	}
}

void	exec_instr(unsigned int instr_id, unsigned int stack_id, t_data *data)
{
	static void (* const instr_table[])(int, t_data *) = {
		swap,
		push,
		rotate,
		rev_rotate
	};

	instr_table[instr_id](stack_id, data);
}

void	exec_instr_loop(int instr_id, int stack_id, int n, t_data *data)
{
	int	i;

	i = 0;
	while (i < n)
	{
		exec_instr(instr_id, stack_id, data);
		save_instr_init(NULL, instr_id, stack_id, data);
		i++;
	}
}

int	stack_ud(t_stack stack, int pos)
{
	return (stack.array[stack.size - (pos + 1)]);
}
