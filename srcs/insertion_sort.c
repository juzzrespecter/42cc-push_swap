#include "push_swap.h"
#include <stdio.h>

/*
 *	falta implementar:
 *		escoger entre rot y rrot 
 *		dependiendo de la posicion del 
 *		elemento a anyadir en sorted stack
 *
 */

static void	add_element_to_sorted_stack(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->stack[S_B].size)
	{
		if (stack_element(data->stack[S_A], 0) > stack_element(data->stack[S_B], i))
			break ;
		i++;
	}
	if (i > data->stack[S_B].size)
		exec_instr_loop(RROT_ID, S_B, data->stack[S_B].size - i, data);
	else
		exec_instr_loop(ROT_ID, S_B, i, data);
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	if (i > data->stack[S_B].size)
		exec_instr_loop(ROT_ID, S_B, data->stack[S_B].size - i, data);
	else
		exec_instr_loop(RROT_ID, S_B, i, data);
}

void	insertion_sort(t_data *data)
{
	int	i;
	int	round;

	i = 0;
	round = data->stack[S_A].size;
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	while (i < round)
	{
		if (stack_element(data->stack[S_A], 0) < stack_element(data->stack[S_B], 0))
			exec_instr_loop(PUSH_ID, S_B, 1, data);
		else
			add_element_to_sorted_stack(data);
		i++;
	}
	exec_instr_loop(PUSH_ID, S_A, round, data);
}
