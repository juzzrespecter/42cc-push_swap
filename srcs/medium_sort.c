#include "push_swap.h"
# define N_PASOS 6 

static int	find_next_down(double pivot, int pass, int index, t_stack stack)
{
	int	pos;

	pos = 0;
	while (pos < pass)
	{
		if (stack_ud(stack, index - pos) < pivot)
			return (pos + 1);
		pos++;
	}
	return (-1);
}

static int	selection_sort_medium_step(double pivot, int pass, t_data *data)
{
	int	next_up;
	int	next_down;
	int	n_rrot;
	int	i;

	n_rrot = 0;
	i = 0;
	while (i < pass)
	{
		next_up = find_next_up(pivot, pass - i, data->stack[S_A]);
		next_down = find_next_down(pivot, n_rrot, data->stack[S_A].size - 1,  data->stack[S_A]);
		if (next_down == -1 && next_up == -1)
			break ;
		if ((next_down < next_up && next_down != -1) || next_up == -1)
		{
			n_rrot += next_down;
			exec_instr_loop(RROT_ID, S_A, next_down, data);
		}
		else
		{
			n_rrot = n_rrot - next_up < 0 ? 0 : n_rrot - next_up;
			exec_instr_loop(ROT_ID, S_A, next_up, data);
		}
		exec_instr_loop(PUSH_ID, S_B, 1, data);
//		sleep(1);
	}
	exec_instr_loop(RROT_ID, S_A, n_rrot, data);
	return (pass - i);
}

static double ft_abs(double a, double b) { if (a < 0) { a *= -1; } return ((a + b)); }

void	selection_sort_medium(t_data *data, int pass)
{
	double	pivot;
	int	bounds[2];
	int	i;

	bounds[0] = stack_ud(data->stack[S_A], find_smallest_number(data->stack[S_A], pass));
	bounds[1] = stack_ud(data->stack[S_A], find_biggest_number(data->stack[S_A], pass));
	i = 0;
//	printf("pass init: (%d)\n", pass);
	while (i < (N_PASOS - 1))
	{
//		printf("pass: (%d)\n", pass);
		pivot = bounds[0] + ( (i + 1) * ft_abs(bounds[0], bounds[1]) ) / N_PASOS;
	//	printf("pivot: (%lf) min: (%d) max: (%d)\n", pivot, bounds[0], bounds[1]);
		pass = selection_sort_medium_step(pivot, pass, data);
		i++;
	}
//	printf("pass fini: (%d)\n", pass);
//	sleep (1);
	selection_sort_small(data, S_A, pass);
	selection_sort_small(data, S_B, data->stack[S_B].size);
}
