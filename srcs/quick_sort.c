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
	median /= (float)recorrido;
	return (median);
}

static double tema(t_stack stack, int r)
{
	double lo, mid, hi;
	double	ret;

	lo = stack_element(stack, 0);
	mid = stack_element(stack, r/2);
	hi = stack_element(stack, r - 1);

	ret = lo > mid ? lo : mid;
	ret = hi > ret ? hi : ret;
	return (lo);
}

/*static int	check(t_stack stack, int size, double pivot)
  {
  int lo, hi;
  int i;

  i = 0;
  while (i < size)
  {
  if (stack_element(stack, i) < pivot)
  lo = i;
  i++;
  }
  i = 0;
  while (i < size)
  {
  if (stack_element(stack, size - (i + 1)) >= pivot)
  hi = size - i;
  i++;
  }
//printf("lo (%d) - (%d)\nhi (%d) - (%d)\nr(%d)\n", lo, stack_element(stack, lo), hi, stack_element(stack, hi), size);
if (lo < hi)
return (!lo ? 1 : lo);
return (0);
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
	pivot = (double)tema(data->stack[S_A], recorrido);
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
			exec_instr_loop(ROT_ID, S_A, j, data); /* se pasa del valor de recorrido, checkar estoo */
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
	exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
	return (n);
}

void	quick_sort(int recorrido, t_data *data)
{	
	int	n;

	// caso ya ordenado
	//
	// caso n == 3
	// caso n == 5
	// caso n == 100
	// caso n == 500
	if (recorrido < 2)
	{
		exec_instr_loop(ROT_ID, S_A, 1, data);
		return ;
	}
	n = particion(recorrido, data);
	quick_sort(n, data);
	quick_sort(recorrido - n, data);
}
