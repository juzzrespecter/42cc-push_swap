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
		if (stack_element(data->stack[S_A], S_A) > stack_element(data->stack[S_B], S_B))
			break ;
		i++;
	}
	exec_instr_loop(ROT_ID, S_B, i, data);
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	exec_instr_loop(RROT_ID, S_B, i, data);
}

void	insertion_sort(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->stack[S_A].size)
	{
		if (stack_element(data->stack[S_A], i) > stack_element(data->stack[S_A], i + 1))
		{
			if (i > 0)
			{
				exec_instr_loop(PUSH_ID, S_B, i, data);
				exec_instr_loop(SWAP_ID, S_A, 1, data);
				add_element_to_sorted_stack(data);
				exec_instr_loop(PUSH_ID, S_A, i + 1, data);
			}
			else
				exec_instr_loop(SWAP_ID, S_A, 1, data);
		}
		i++;
	}
}
