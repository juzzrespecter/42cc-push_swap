#include "push_swap.h"

/*
 * recursivo??
 *
 * condicion de sainda: rango del subarray es menor que 2
 *
 * escoger un pivot (criterios: ultimo elemento del array (worst_case scenario !!)
 * particion: crear dos sub arrays separados por el pivot, uno con todos los valores mayores que este
 * 			  y otro con los valores menores
 * aplicar recursion a los dos subarrays
 *
 * in-place - los sub arrays sigue formando parte del mismo stack a (no es necesario usar mas memoria con nuevos arrays)
 *
 * quicksort ( A, lo, hi )
 * 		if lo < hi then;
 * 			p := partition ( A, lo, hi )
 * 			quicksort ( A, lo,    p - 1 )
 * 			quicksort ( A, p + 1, hi    )
 *
 * partition ( A, lo, hi )
 * 		pivot := A [ hi ]					-> seleccion de pivot como el ultimo elemento del array
 * 		i	  := lo
 * 		for j := lo to hi
 * 			if A [ j ] < pivot then			-> encontrado elemento menor que el pivot
 * 				swap A [ i ] with A [ j ]	-> movemos el elemento a la parte izquierda del array
 * 				i := i + 1					-> ese elemento no vuelve a ser comparado
 * 		swap A [ i ] with A [ hi ]			-> movemos el pivot a la posicion que separa los dos arrays
 * 		return i							-> devuelve la posicion que separa el array en dos sub arrays
 *
 *
 * pivot: A [ hi ] como pivot provoca complejidad O ( n^2 ) en casos de array con tendencia a ordenacion inversa
 * 
 * para acercar la complejidad del algoritmo al caso estandar O( n * log(n) ), pueden usarse otros criterios de seleccion de pivot:
 * -> escoger un elemento aleatorio de la lista
 * -> precalcular el elemento que se situara en la mitad de la lista (asegurando un comportamiento O(n * log(n)) para cualquier caso)
 * -> comparar entre el primer elemento, el elemento de mitad de la lista y el ultimo, usando el valor del medio como pivot
 */

void	quick_sort(t_data *data)
{
	check_already_sorted();

}
