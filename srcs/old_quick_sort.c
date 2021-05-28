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

/*static int	finished_criba(t_stack stack, int i_rest, int rec, double pivot)
  {
  int	count = 1;

  while (i_rest + count < rec)
  {
  if ((double)stack_element(stack, count) < pivot)
  return (0);
  count++;
  }
  return (1);
  }*/

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

	//n = check(data->stack[S_A], recorrido, pivot);
	//	printf("n: (%d), r (%d).\n", n, recorrido);
	//if (n != 0)
	//	return (n);
	if (recorrido == data->stack[S_A].size)
		test = 1;
	while (i < recorrido)
	{
		if ((double)stack_element(data->stack[S_A], j) < pivot)
		{
			tmp += j;
			exec_instr_loop(ROT_ID, S_A, j, data);
			//			if (!finished_criba(data->stack[S_A], i, recorrido, pivot))
			//			{
			exec_instr_loop(PUSH_ID, S_B, 1, data);
			// checkear cuando pushea de mas
			j = 0;
			//			}
			//			else
		}
		else
			j++;
		i++;
	}

	n = data->stack[S_B].size == 0 ? 1 : data->stack[S_B].size;
	if (test == 0)
		exec_instr_loop(RROT_ID, S_A, tmp, data);
	exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
	return (n);
}

/*static void	check_three(int first, int second, int third, t_data *data)
{
	if (first < second && second < third)
		return ;
	if (second > first && second < third)
	{
		exec_instr_loop(SWAP_ID, S_A, 1, data);
		return ;
	}
	if (second > first && second > third)
	{
		exec_instr_loop(PUSH_ID, S_B, 1, data);
		exec_instr_loop(SWAP_ID, S_A, 1, data);
		exec_instr_loop(PUSH_ID, S_A, 1, data);
		return ; 
	}
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	exec_instr_loop(SWAP_ID, S_B, 1, data);
	exec_instr_loop(PUSH_ID, S_A, 1, data);
	exec_instr_loop(PUSH_ID, S_A, 1, data);
	return ;

}*/

/*static void	quick_sort(int recorrido, t_data *data)
{	
	int	n;

	// caso ya ordenado
	//
	//init sort: escoge algoritmo depende del input:
	//size = 0 a n (a calcular) -> small sort
	//size = n a inf (de momento) -> quick sort

	// recorrido == 3
	// recorrido == 4
	// recorrido == 5
	// recorrido == 6

	if (recorrido ==  1)
	{
		exec_instr_loop(ROT_ID, S_A, 1, data);
		return ;
	}
	*
	 * if recorrido == 2
	 * 	cosas
	 *
	 *
	if (check_already_sorted(data->stack[S_A], recorrido))
	{
		exec_instr_loop(ROT_ID, S_A, recorrido, data);
		return ;
	}
	if (recorrido == 2)
	{
		if (stack_element(data->stack[S_A], 0) > stack_element(data->stack[S_A], 1))
			exec_instr_loop(SWAP_ID, S_A, 1, data);
		if (!(data->stack[S_A].size == recorrido))
			exec_instr_loop(ROT_ID, S_A, 2, data);
		return ;
	}
	if (recorrido == 3)
	{
		check_three(stack_element(data->stack[S_A], 0), \
				stack_element(data->stack[S_A], 1), \
				stack_element(data->stack[S_A], 2), \
				data);
		if (!(data->stack[S_A].size == recorrido))
			exec_instr_loop(ROT_ID, S_A, 3, data);
		return ;
	}
	n = particion(recorrido, data);
	quick_sort(n, data);
	quick_sort(recorrido - n, data);
} */

/*static void	stack_three()
{
	func check_if_only_three(); // metemos rr
	...;
}

static void	stack_four()
{
	
}*/

static void quick_sort(int recorrido, t_data *data)
{
	int	n;

	if (recorrido == 1)
	{
		exec_instr_loop(ROT_ID, S_A, 1, data);
		return ;
	}
	if (recorrido == 2)
	{
		if (stack_element(0;
	}


}

void	quick_sort_init(t_data *data)
{
	if (check_already_sorted(data->stack[S_A], data->stack[S_A].size))
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	quick_sort(data->stack[S_A].size, data);
}

/*
 *
 * A = 1; ret
 * A = 2; s, ret
 * A = 3; { n = 3, n != 3, rr }
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
