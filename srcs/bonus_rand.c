#include "push_swap.h"

static t_stack fill_stack_with_best_case(int n_elem)
{
	t_stack	stack_a;
	int	i;

	stack_a.size = n_elem;
	stack_a.array = (int *)malloc(sizeof(int) * n_elem);
	if (stack_a.array == NULL)
		err_and_exit(NULL, NULL, E_NOMEM);
	i = 0;
	while (i < n_elem)
	{
		stack_a.array[i] = i;
		i++;
	}
	return (stack_a);
}

static t_stack fill_stack_with_worst_case(int n_elem)
{
	t_stack	stack_a;
	int	i;
	
	stack_a.size = n_elem;
	stack_a.array = (int *)malloc(sizeof(int) * n_elem);
	if (stack_a.array == NULL)
		err_and_exit(NULL, NULL, E_NOMEM);
	i = 0;
	while (i < n_elem)
	{
		stack_a.array[i] = n_elem - i;
		i++;
	}
	return (stack_a);
}

static int	is_duplicate(int to_add, int *array, int array_pos)
{
	int	i;

	i = 0;
	while (i < array_pos)
	{
		if (array[i] == to_add)
			return (1);
		i++;
	}
	return (0);
}

t_stack	fill_stack_with_rand(int start, char **argv)
{
	t_stack stack_a;
	int	n_elem;
	int	to_add;
	int	i;

	n_elem = ft_atoi(argv[start]);
	if (argv[start + 1] != NULL)
	{
		if (argv[start + 1][0] ==  'B')
			return (fill_stack_with_best_case(n_elem));
		else
			return (fill_stack_with_worst_case(n_elem));
	}
	i = 0;
	stack_a.size = n_elem;
	stack_a.array = (int *)malloc(sizeof(int) * n_elem);
	if (stack_a.array == NULL)
		err_and_exit(NULL, NULL, E_NOMEM);
	srand(time(0));
	while (i < n_elem)
	{
		to_add = 2 * (rand() % INT_MAX) + INT_MIN;
		if (!is_duplicate(to_add, stack_a.array, i))
		{
			stack_a.array[i] = to_add;
			i++;
		}
	}
	return (stack_a);
}
