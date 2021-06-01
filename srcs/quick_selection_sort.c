#include "push_swap.h"
# define SMALL_LIMIT 15 
# define MEDIUM_LIMIT 150 

static void	choose_stack_bounds(int *bounds, t_stack stack,  int pass)
{
	bounds[0] = stack_ud(stack, find_smallest_number(stack, pass));
	bounds[1] = stack_ud(stack, find_biggest_number(stack, pass));
}

static double	choose_pivot(t_data *data,  int pass)
{
	int	bounds[2];

	choose_stack_bounds(bounds, data->stack[S_A], pass);
	return ((double)(((double)bounds[0] + (double)bounds[1]) / 2));
}

static int	quick_sort_partition(t_data *data,  int pass)
{
	double pivot;
	int	first_step;
	int test;
	int	pos;
	int	i;

	pivot = choose_pivot(data, pass);
	i = 0;
	test = 0;
	first_step = (data->stack[S_A].size == pass);
	while (i < pass)
	{
		pos = find_next_up(pivot, pass - i, data->stack[S_A]);
		if (pos < 0)
			break ;
		test += pos;
		exec_instr_loop(ROT_ID, S_A, pos, data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
		i += pos + 1;
	}
	exec_instr_loop(RROT_ID, S_A, test * (first_step == 0), data);
	return (data->stack[S_B].size + 1 * (data->stack[S_B].size == 0));
}

static void	quick_sort(t_data *data,  int pass)
{
	int	n_b;

	if (pass < 2)
	{
		exec_instr_loop(ROT_ID, S_A, 1, data);
		return ;
	}
	if (check_if_sorted(data->stack[S_A], pass))
	{
		exec_instr_loop(ROT_ID, S_A, pass, data);
		return ;
	}
	if (pass < 50)
	{
		selection_sort_medium(data, pass);
		exec_instr_loop(ROT_ID, S_A, pass, data);
		return ;
	}
	n_b = quick_sort_partition(data, pass);
	exec_instr_loop(PUSH_ID, S_A, n_b, data);
	quick_sort(data, n_b);
	quick_sort(data, pass - n_b);
}

void	quick_sort_init(t_data *data)
{
	if (check_if_sorted(data->stack[S_A], data->stack[S_A].size))
		return ;
	if (data->stack[S_A].size < SMALL_LIMIT)
	{
		selection_sort_small(data, S_A, data->stack[S_A].size);
		exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
	}
	else if (data->stack[S_A].size < MEDIUM_LIMIT)
		selection_sort_medium(data, data->stack[S_A].size);
	else
		quick_sort(data, data->stack[S_A].size);
}
