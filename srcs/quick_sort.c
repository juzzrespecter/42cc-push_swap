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

static void	partition(t_data *data, int low, int high)
{
	/*
	 * select pivot
	 * while (i + low < high)
	 * if data->stack_a->array[index_pos(i + low)]
	 * 	pb
	 * 	i++;
	 * while (data->stack_b->size)
	 * 	pa
	 * ret;
	 */

	int	i;
	int	pivot;

	i = 0;
	pivot = data->stack_a->array[index_pos(data->stack_a, high)]; // provisional
	while (i + low < high)
	{
		if (data->stack_a->array[index_pos(data->stack_a, i + low)] < pivot)
			exec_cmd(data, "pb", 1);
		i++;
	}
}

static void	quick_sort(t_data *data, int i, int j)
{
	int	pos;

	pos = partition(data, i, j);
	quick_sort(data, i, j - pos);
	quick_sort(data, i + pos, j);
}

void	quick_sort_init(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = data->stack_a->size;	
	check_already_sorted(data->stack_a);
	quick_sort(data, i, j);
}
