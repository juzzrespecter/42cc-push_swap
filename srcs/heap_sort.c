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

/*
 *	coge bien los indices
 *	parece que falla a la hora de meter el ultimo paso, justo
 *	cuando llega al root
 *
 *
 */


#include "push_swap.h"
#include <stdio.h>

static void heapify_up(int n, int i, t_data *data)
{
	if (n < 0)
	{
		exec_cmd("rra", 1, data);
		return ;
	}
	exec_cmd("pa", 1, data);
	exec_cmd("rrb", i, data);
	heapify_up(n - 1, i / 2, data);
	exec_cmd("pb", 1 , data);
	exec_cmd("rb", i, data);	
}

static int	n_of_recursions(int leaf, t_stack heap)
{
	int	n;
	int	i;
	int	parent;

	n = 0;
	i = (heap.size + 1) / 2;
	parent = heap.array[index_pos(heap, i - 1)];
//	printf("son: %d, parent: %d\n", leaf, parent);
//	printf("i: (%d), index_pos: (%d)\n", i, index_pos(heap, i - 1));
	while (leaf > parent && i > 0)
	{
//		printf("---while---\nson: %d, parent: %d\n", leaf, parent);
//		printf("i: (%d), index_pos: (%d)\n", i, index_pos(heap, i - 1));
		n++;
		i /= 2;
		parent = heap.array[index_pos(heap, i - 1)];
	}
//	printf("n: (%d)\n", n);
	return (n);
}

static void	heapify(int leaf, t_data *data)
{
	t_stack stack;
	t_stack heap;
	int	i;
	int	n;

	stack = data->stack_a;
	heap = data->stack_b;
	if (heap.size == 0)
	{
		exec_cmd("pb", 1, data);
		return ;
	}
	n = n_of_recursions(leaf, heap);
	if (n > 0)
	{
		i = heap.size / 2;
		exec_cmd("rr", 1, data);				// guarda elemento a pushear
		exec_cmd("rb", i - 1, data);	// mueve a primer parent
		heapify_up(n - 1, i, data);
		exec_cmd("rrb", i, data);
	}
	exec_cmd("pb", 1, data);				// mete el elemento hoja
	exec_cmd("rb", 1, data);
}

static void	delete_from_heap(t_data *data)
{
	int	n;

	n = data->stack_a.array[index_pos(data->stack_a, 0)];
	exec_cmd("pa", 1, data);
	if (data->stack_b.size == 0)
		return ;
	exec_cmd("rrb", 1, data);
	exec_cmd("pa", 1, data);
	heapify(n, data);
}

void	heap_sort(t_data *data)
{
	int	stack_size;
	int	son;
	int	i;

	stack_size = data->stack_a.size;
	i = 0;
	while (i < stack_size)
	{
		son = data->stack_a.array[index_pos(data->stack_a, 0)];
		heapify(son, data);
		i++;
	}
	i = 0;
	while (i < stack_size)
	{
		delete_from_heap(data);
		i++;
	}
}
