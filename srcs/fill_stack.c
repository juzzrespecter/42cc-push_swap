#include "push_swap.h"

t_stack	fill_stack(char **argv)
{
	t_stack	stack_s;
	int	count;
	/*
	 * get stack size
	 * malloc stack
	 * fill stack (atoi)
	 */
	count = 0;
	stack_s.size = 0;
	while (argv[stack_s.size])
		stack_s.size++;
	stack_s.stack = (int *)malloc(sizeof(int) * stack_s.size);
	if (stack_s.stack == NULL)
		err_and_exit(NULL);
	/* mirar orden de llenado del stack	*/
	while (argv[count])
	{
		stack_s.stack[count] = ft_atoi(argv[count]);
		count++;
	}
	return (stack_s);
}

