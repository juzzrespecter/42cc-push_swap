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

/*
 * choose_pivot(); ->criterio
 * recorrido de la particion (recorre todo el size de la particion)
 * orden de las particiones (elementos mayores en top ??)
 */
#include <stdio.h>

/*static int	check_if_sorted(int part_size, t_data *data)
  {
  int	i;

  i = 0;
  while (i < part_size)
  {
  if (data->stack_a.array[i] < data->stack_a.array[i + 1])
  return (0);
  i++;
  }
  return (1);
  }*/
/*
 *
 *	si encuentra en el recorrido de la particion un numero menor que el 
 *	pivot, ra * x, pb
 *
 *	termina el recorrido, ya sea por no elementos < pivot o i > recorrido:
 *	rra * x + pb * size
 *
 *	size es el recorrido de la siguiente particion, devolver a quick sort
 *
 *	quick sort llama a quick sort(size)
 *					   quick sort (recorrido - size)
 *
 *	condicion de salida de la recursion: recorrido < 2; pasamos el elemento
 *	ordenado a la parte de abajo del stack (??)
 */
#include <stdio.h>

static int	pivot_as_median(t_stack stack, int recorrido)
{
	long	median;
	int i;

	median = 0;
	i = 0;
	while (i < recorrido)
	{
		median += stack.array[index_pos(stack, i)];
		i++;
	}
	median /= recorrido;
	//printf("mediana calculada: (%ld)\n", median);
	return ((int)median);
}

static int	particion(int recorrido, t_data *data)
{
	int	pivot;
	int	tmp;
	int	n;
	int	i;
	int	j;

	pivot = pivot_as_median(data->stack_a, recorrido);
	//pivot = data->stack_a.array[index_pos(data->stack_a, 0)];
	tmp = 0;
	i = 0;
	j = 0;
	while (i < recorrido)
	{
		if (data->stack_a.array[index_pos(data->stack_a, j)] < pivot)
		{
			tmp += j;
			exec_cmd("ra", j, data); /* se pasa del valor de recorrido, checkar estoo */
			exec_cmd("pb", 1, data);
			j = 0;
		}
		else
			j++;
		i++;
	}
	n = data->stack_b.size == 0 ? 1 : data->stack_b.size;
	exec_cmd("rra", tmp, data);
	exec_cmd("pa", data->stack_b.size, data);
	return (n);
}

void	quick_sort(int recorrido, t_data *data)
{	
	int	n;

	if (recorrido < 2)
	{
		exec_cmd("ra", 1, data);
		return ;
	}
	n = particion(recorrido, data);
	quick_sort(n, data);
	quick_sort(recorrido - n, data);
}
