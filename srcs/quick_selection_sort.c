#include "push_swap.h"

static double	choose_pivot(t_stack stack, int recorrido)
{
	int	i;
	double	pivot;

	i = 0;
	pivot = 0;
	while (i < recorrido)
	{
		pivot += (double)stack_ud(stack, i);
		i++;
	}
	return (pivot / (float)i);
}

static int	partition_more(t_data *data, int from, int to, int rec, double pivot)
{
	int	i = 0;
	int	pos = 0;

	while (i < rec)
	{
		if (stack_ud(data->stack[from], pos) > pivot)
		{
			exec_instr_loop(ROT_ID, from, pos, data);
			exec_instr_loop(PUSH_ID, to, 1, data);
			pos = 0;
		}
		else
			pos++;
		i++;
	}
	return (data->stack[from].size + 1 * (data->stack[from].size == 0));
}

static int	partition_less(t_data *data, int from, int to, int rec, double pivot)
{
	int	i = 0;
	int	pos = 0;

	printf("------------------------------------------------------------------------------\n");
	while (i < rec)
	{
		printf("step... (%d) (%d) (%lf)\n", rec, stack_ud(data->stack[from], pos), pivot);
		if (stack_ud(data->stack[from], pos) < pivot)
		{
			exec_instr_loop(ROT_ID, from, pos, data);
			exec_instr_loop(PUSH_ID, to, 1, data);
			pos = 0;
		}
		else
			pos++;
		i++;
	}
	return (data->stack[from].size + 1 * (data->stack[from].size == 0));
}

static int	find_smallest(t_stack stack)
{
	int	i;
	int	smallest;
	int	smallest_pos;

	i = 0;
	smallest = stack_ud(stack, 0);
	while (i < stack.size)
	{
		if (stack_ud(stack, i) < smallest)
		{
			smallest = stack_ud(stack, i);
			smallest_pos = i;
		}
		i++;
	}
	return (smallest_pos);
}
static int	find_biggest(t_stack stack)
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_ud(stack, 0);
	while (i < stack.size)
	{
		if (stack_ud(stack, i) > biggest)
		{
			biggest = stack_ud(stack, i);
			biggest_pos = i;
		}
		i++;
	}
	return (biggest_pos);
}

static void	selection_sort_f(t_data *data, int from, int to, int rec)
{
	if (rec == 0)
		return ;
	int pos;
	
	if (from == S_A)
		pos = find_smallest(data->stack[from]);
	else
		pos = find_biggest(data->stack[from]);
	if (pos < data->stack[from].size / 2)
		exec_instr_loop(ROT_ID,from,  pos, data);
	else
		exec_instr_loop(RROT_ID, from, data->stack[from].size - pos, data);
	exec_instr_loop(PUSH_ID, to,1, data);
	selection_sort_f(data, from, to, rec - 1);
}

static void	quick_sort(t_data *data, int from, int to, int rec, int index, double pivot)
{
	int 	n;

	if (data->stack[from].size == 0)
	{
		selection_sort_f(data, to, from, rec);
		return ;
	}
	if (from == S_A)
		n = partition_less(data, from, to, rec, (index + 1) * pivot / 4);
	else
		n = partition_more(data, from, to, rec, 2 * pivot - ((index + 1) * pivot / 4));
	quick_sort(data, from, to, n, index + 1, pivot);
}
void	quick_sort_init(t_data *data)
{
	/*
	 * 1.- partir el array en dos sub arrays de mas o menos mismo tamano
	 *
	 * 2.- quick_sort b de mayor a menor, push a stack b
	 *
	 * 3.- selection sort a -> b de unicamente los elementos quick_sort
	 *
	 * 4.- quick_sort a -> b de menor a mayor
	 *
	 * 5.- selection sort b -> a
	 *
	 * 6.- push b -> a
	 *
	 */

/*
 *
 * check pivot criteria (max - min) / 2
 *
 */

	double pivot;
	int n_a;
	//int n_b;
	
	//pivot = choose_pivot(data->stack[S_A], data->stack[S_A].size);
	//partition_less(data, S_A, S_B, data->stack[S_A].size, pivot);
	n_a = data->stack[S_A].size;
	//n_b = data->stack[S_B].size;
	//pivot = choose_pivot(data->stack[S_B], data->stack[S_B].size);
	//quick_sort(data, S_B, S_A, n_b, 0, pivot);
	//selection_sort_f(data, S_A, S_B,  n_b);
	pivot = choose_pivot(data->stack[S_A], data->stack[S_A].size);
	quick_sort(data, S_A, S_B, n_a, 0, pivot);
	selection_sort_f(data, S_B, S_A,  n_a);
	exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
}
