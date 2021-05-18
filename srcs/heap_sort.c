/*
 * Heap sort:
 * 		Algoritmo de ordenacion por seleccion.
 * 		Organizar el stack de entrada como un heap en el stack auxiliar (stack_b).
 * 		Eliminar los elementos root del heap, que formaran el array ya ordenado
 * 		de vuelta al stack de salida.
 *
 *		( stack_a == stack original )
 *		( stack_b == heap )
 *
 *		1.- n * heapify (construye el heap)
 *		2.- n * delete_from_heap (push a b todos los roots del heap)
 *		3.- Devolver el array de elementos ordenados al stack (push a a)
 *
 *		traduccion arbol binario - array:
 *			-> hijo izquierdo de un elemento i: i * 2
 *			-> hijo derecho de un elemento i:   i * 2 + 1
 *			-> padre de un elemento i:		    floor(i / 2)
 *
 *		heapify - insertar el elemento en la ultima hoja disponible, despues ir 
 *				  subiendo por los sucesivos padres mientras sean menores que el
 *				  elemento hasta encontrar su posicion en el heap
 *
 *		delete -  el primer elemento (root) siempre sera el mayor en un max heap
 *				  push el elemento de vuelta al stack y: escoger de entre los hijos
 *				  el mayor y situarlo en el root, y de forma recursiva cubrir el 
 *				  hueco dejado por el primer hijo con el mayor de sus hijos hasta llegar
 *				  al final del heap 
 *
 * 		complejidad del algoritmo: O( n * log(n) ), donde n == stack_a.size
 * 		en cualquier caso.
 *
 * 		heapify == (...) + pb
 * 		delete == (...) + pa
 */

#include "push_swap.h"
#include <stdio.h>

static void	ordenar_stack(t_data *data, int n)
{
	int	i;

	i = 0;
	exec_cmd("pa", 1, data);
	while (i < n)
	{
		exec_cmd("sa", 1, data);
		exec_cmd("ra", 1, data);
		i++;
	}
	exec_cmd("rra", n, data);
}

static void segunda_iteracion(int i, int new, int n_stack, t_data *data)
{
	int	parent;

	exec_cmd("rrb", i, data);
	ordenar_stack(data, n_stack);
	parent = data->stack_b.array[i/2 - 1];
	if (new > parent && i > 0)
		segunda_iteracion(i/2, new, n_stack++, data);
	exec_cmd("pb", 1, data);
	exec_cmd("rb", i, data);
}

static void	primera_iteracion(int i, int new, t_data *data)
{
	int	parent;

	exec_cmd("rb", i, data);
	ordenar_stack(data, 1);
	parent = data->stack_b.array[i/2 - 1];
	if (new > parent && i > 0)
		segunda_iteracion(i/2, new, 2, data);
	exec_cmd("pb", 1, data);
	exec_cmd("rrb", i, data);
}

static void	heapify(/* valor a comparar, stack, heap */int new, t_data *data)
{
	t_stack stack;
	t_stack heap;
	int	parent;
	int	i;

	/*
	 * i == indice para moverse por heap
	 * index_pos(i) == posicion real del elemento en el array
	 * 		( index_pos(i) == size - i )
	 * 		i := { i(new) == size, i(root == top stack) == 1 }
	 *
	 * if ( primer_elemento )
	 * 		pb, ret;
	 * set up i, new, parent:
	 * 		i 	= size / 2
	 * 		new = stack[size - 1]
	 * 		parent = heap[index_pos(i + 1)] -> i rang [ 1, size ]
	 * while ( new > parent )
	 * 		mover heap (rb) hasta encontrar parent
	 * 		recogemos todos los parents menores que new y los ordenamos de forma inversa en stack (pa + (sa * ra) * n + rra * n )
	 *		condicion new < parent: hacemos pb a todos los elementos almacenados temporalmente en sus respectivas posiciones
	 *		primera_iteracion()
	 *		{
	 *			if new > parent
	 *			{
	 *				rb * i
	 *				ordenar stack ( pa + (sa * ra ) * n_de_movimientos + rra * n_de_movimientos )	
	 *				segunda_iteracion();
	 *				rrb * i
	 *			}
	 *			pb;
	 *			rb;
	 *		}
	 *
	 * 		segunda_iteracion()
	 * 		{
	 * 			cambio de criterio para los indices: index_pos(i + 1) -> i - 1
	 *			
	 *			i     /= 2;
	 * 			new    = cnst.
	 * 			parent = heap[i - 1]
	 * 			if new > parent
	 * 			{
	 * 				ordenar_stack(data, n);
	 * 				i * rrb;
	 * 				segunda_iteracion();
	 * 				i * rb;
	 * 				pb
	 * 			}
	 * 			ret;
	 * 		}
	 *
	 *
	 *
	 *
	 */
	stack = data->stack_a;
	heap = data->stack_b;
	if (heap.size == 0)
	{
		exec_cmd("pb", 1, data);
		return ;
	}
	i = heap.size / 2;
	parent = heap.array[index_pos(heap, i + 1)];
	if (new > parent)
		primera_iteracion(i, new, data);
	exec_cmd("pb", 1, data);
	exec_cmd("rb", 1, data);
}

/*static void	delete_from_heap(t_data *data)
{
	int	n;

	n = data->stack_a->array[index_pos(data->stack_a, 0)];
	cmd_loop(data, "pa", 2);
	* guarda el root
	 * pilla el ultimo elemento en el stack (rb, pa)
	 * llama a heapify para que inserte ese elemento
	 *
	heapify(n, data);
}*/

void	heap_sort(t_data *data)
{
	int	stack_size;
	int	new;
	int	i;

	stack_size = data->stack_a.size;
	i = 0;
	while (i < stack_size)
	{
		new = data->stack_a.array[index_pos(data->stack_a, 0)];
		heapify(new, data);
		i++;
	}
	i = 0;
	/*while (i < stack_size)
	{
		delete_from_heap(data);
		i++;
	}*/
}
