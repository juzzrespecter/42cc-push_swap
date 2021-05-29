#include "push_swap.h"

/*
 * Quick sort:
 * 		algortmo de ordenacion recursivo por comparacion, escoge un elemento 'pivot' que se usara
 * 		para separar el array en dos sub-arrays, un conteniendo todos los elementos
 * 		menores que el elemento pivot, y otro conteniendo los elementos mayores, para 
 * 		despues llamar a quick sort en cada uno de estos sub-arrays que ordenaran
 * 		en distintos sub-arrays de forma recursiva hasta alcanzar la condicion de salida
 * 		en la que el rango del sub-array es menor que 2 (la menor unidad posible)
 *
 * pivot: A [ hi ] como pivot provoca complejidad O ( n^2 ) en casos de array con tendencia a ordenacion inversa
 * 
 * para acercar la complejidad del algoritmo al caso estandar O( n * log(n) ), pueden usarse otros criterios de seleccion de pivot:
 * -> escoger un elemento aleatorio de la lista
 * -> precalcular el elemento que se situara en la mitad de la lista (asegurando un comportamiento O(n * log(n)) para cualquier caso)
 * -> comparar entre el primer elemento, el elemento de mitad de la lista y el ultimo, usando el valor del medio como pivot
 */

#include <stdio.h>

/*static int	push_front(t_stack stack, double pivot)
{
	int	pos;

	pos = 0;
	while (pos < stack.size)
	{
		if ((double)stack_element(stack, pos) < pivot)
			return (pos);
		pos++;
	}
	return (-1);
}*/

static double	choose_pivot(t_stack stack, int recorrido)
{
	double	median;
	int count;
	int i;

	median = 0;
	count = 0;
	i = 0;
	while (i < recorrido && count < recorrido/2)
	{
		median += stack_element(stack, i);
		i++;
	}
	median /= (double)recorrido;
	return (median);
}

static int	particion(int recorrido, t_data *data)
{
	double	pivot;
	int	tmp;
	int	n;
	int	i;
	int	j;
	int	test = 0;

	pivot = choose_pivot(data->stack[S_A], recorrido); // best
	tmp = 0;
	i = 0;
	j = 0;

	if (recorrido == data->stack[S_A].size)
		test = 1;
	while (i < recorrido)
	{
		if ((double)stack_element(data->stack[S_A], j) < pivot)
		{
			tmp += j;
			exec_instr_loop(ROT_ID, S_A, j, data);
			exec_instr_loop(PUSH_ID, S_B, 1, data);
			j = 0;
		}
		else
			j++;
		i++;
	}
	n = data->stack[S_B].size == 0 ? 1 : data->stack[S_B].size;
	if (test == 0)
		exec_instr_loop(RROT_ID, S_A, tmp, data);
	return (n);
}

static int	find_biggest(t_stack stack)
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_element(stack, 0);
	while (i < stack.size)
	{
		if (stack_element(stack, i) > biggest)
		{
			biggest = stack_element(stack, i);
			biggest_pos = i;
		}
		i++;
	}
	return (biggest_pos);
}

static void	selection_sort_subarray(t_data *data)
{
	int pos;

	if (data->stack[S_B].size == 0)
		return ;
	if (data->stack[S_B].size == 2)
	{
		if (stack_element(data->stack[S_B], 0) < stack_element(data->stack[S_B], 1))
			exec_instr_loop(SWAP_ID, S_B, 1, data);
		exec_instr_loop(PUSH_ID, S_A, 2, data);
		return ;
	}
	pos = find_biggest(data->stack[S_B]);
	if (pos < data->stack[S_B].size / 2)
		exec_instr_loop(ROT_ID, S_B, pos, data);
	else
		exec_instr_loop(RROT_ID, S_B, data->stack[S_B].size - pos, data);
	exec_instr_loop(PUSH_ID, S_A, 1, data);
	selection_sort_subarray(data);
}

/*static int	push_back(t_stack stack, double pivot)
{
	int	pos;

	pos = 0;
	while (pos < stack.size)
	{
		if ((double)stack.array[pos] < pivot)
			return (pos);
		pos++;
	}
	return (-1);
}*/

/*static	int exec_first_step(t_data *data)
{
	double	pivot;
	int	count;
	int	rec;
	int	i, j;

	pivot = choose_pivot(data->stack[S_A], data->stack[S_A].size);
	count = 0;
	rec = data->stack[S_A].size;
	while (count < rec)
	{
		i = push_front(data->stack[S_A], pivot);
		if (i == -1)
			break ;
		j = push_back(data->stack[S_A], pivot);
		if (i > j)
			exec_instr_loop(RROT_ID, S_A, j + 1, data);
		else
			exec_instr_loop(ROT_ID, S_A, i, data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
		count++;
	}
	return (data->stack[S_B].size);
}*/

static void	quick_sort(int recorrido, t_data *data)
{	
	int	n;

	if (check_already_sorted(data->stack[S_A], recorrido))
	{
		exec_instr_loop(ROT_ID, S_A, recorrido, data);
		return ;
	}
//	if (recorrido == data->stack[S_A].size)
//		n = exec_first_step(data);
	else
		n = particion(recorrido, data);
	if (data->stack[S_B].size <= 30)
	{
		n = data->stack[S_B].size;
		selection_sort_subarray(data);
	}
	else
		exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
	quick_sort(n, data);
	if (recorrido - n <= 30)
	{
		exec_instr_loop(PUSH_ID, S_B, recorrido - n, data);
		selection_sort_subarray(data);
	}
	quick_sort(recorrido - n, data);
}

void	quick_sort_init(t_data *data)
{
	if (check_already_sorted(data->stack[S_A], data->stack[S_A].size))
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	if (data->stack[S_A].size <= 30)
		selection_sort(data);
	else
		quick_sort(data->stack[S_A].size, data);
}
