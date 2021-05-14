#include "push_swap.h"

/*	insertion sort basico:
 *	stack_b: guarda la sublista ordenada cuando se encuentra un elemento
 *			 desordenado en stack_a
 *	-> encuentra un elemento desordenado en a
 *	-> hace push a la sublista ordenada a b
 *	-> compara el elemento con el resto de la sublista para encontrar su posicion
 *	-> insercion en sublista: pos i - ra * i + pa + rra * i
 */

void	insert_on_sublist(t_stack *stack_a, t_stack *stack_b)
{
	int	pos;
	int	count;
	int	aux;

	pos = 0;
	count = 0;
	aux = stack_a->stack[stack_a->size - 1];
	while (aux < stack_b->stack[stack_b->size - 1 - pos] \
			&& pos < stack_b->size)
		pos++;
	while (count < pos)
	{
		rotate(stack_b);
		ft_putstr("rb\n");
		count++;
	}
	push(stack_b, stack_a);
	ft_putstr("pb\n");
	count = 0;
	while (count < pos)
	{
		rev_rotate(stack_b);
		ft_putstr("rrb\n");
		count++;
	}
}

void	insertion_sort(t_data *data)
{
	t_stack	*stack_a;

	// comprobar que ya esta ordenado
	stack_a = data->stack_a;
	while (stack_a->size)
	{
		if (stack_a->stack[stack_a->size - 1] \
				< stack_a->stack[stack_a->size - 2])
		{
			push(data->stack_b, stack_a);
			ft_putstr("pb\n");
		}
		else
		{
			swap(stack_a);
			ft_putstr("sa\n");
			insert_on_sublist(stack_a, data->stack_b);
		}
	}
	while (data->stack_b->size)
	{
		push(data->stack_a, data->stack_b);
		ft_putstr("pa\n");
	}
}
