#include "push_swap.h"

/*
 * Heap sort:
 * 		Algoritmo de ordenacion por seleccion.
 * 		Organizar el stack de entrada como un heap en el stack auxiliar (stack[S_B]).
 * 		Eliminar los elementos root del heap, que formaran el array ya ordenado
 * 		de vuelta al stack de salida.
 *
 *		( stack[S_A] == stack original )
 *		( stack[S_B] == heap )
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
 * 		complejidad del algoritmo: O( n * log(n) ), donde n == stack[S_A].size
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

static int	n_of_recursions(int leaf, t_stack heap)
{
	int	i;
	int	n;
	int	parent;

	i = (heap.size + 1) / 2;
	n = 0;
	parent = heap.array[i - 1];
	while (leaf > parent && i > 0)
	{
		i = i / 2;
		parent = heap.array[i - 1];
		n++;
	}
	return (n);
}

static void	heapify(int i, int n, t_data *data)
{
	if (n == 0 || data->stack[S_B].size == 0)
	{
		exec_instr_loop(RROT_ID, S_A, 1, data);
		exec_instr_loop(PUSH_ID, S_B, 1, data);
		return ;
	}
	exec_instr_loop(ROT_ID, S_B, i, data);
	exec_instr_loop(PUSH_ID, S_A, 1, data);
	heapify(i / 2, n - 1, data);
	exec_instr_loop(RROT_ID, S_B, i, data);
	exec_instr_loop(PUSH_ID, S_B, 1, data);
}

void	heap_sort(t_data *data)
{
	int	count[2];
	int	size;
	int	leaf;
	int	n;

	size = data->stack[S_A].size;
	ft_bzero(count, 2 * sizeof(int));
	while (count[0] < size)
	{
		leaf = stack_element(data->stack[S_A], 0);
		n = n_of_recursions(leaf, data->stack[S_B]);
		exec_instr_loop(ROT_ID, S_A, 1, data);
		heapify((data->stack[S_B].size + 1) / 2, n, data);
		count[0]++;
	}
	while (count[1] < size)
	{
		if (data->stack[S_B].size == 0)
			return ;
		exec_instr_loop(RROT_ID, S_B, 1, data);
		exec_instr_loop(PUSH_ID, S_A, 2, data);
		leaf = stack_element(data->stack[S_A], 0);
		n = n_of_recursions(leaf, data->stack[S_B]);
		heapify((data->stack[S_B].size + 1) / 2, n, data);
		count[1]++;
	}
}
