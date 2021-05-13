#include "push_swap.h"

static t_stack	*fill_stack(t_stack *stack_s, char **argv)
{
	int	count;

	count = 0;
	stack_s->size = 0;
	while (argv[stack_s->size + 1])
		stack_s->size++;
	stack_s->stack = (int *)malloc(sizeof(int) * stack_s->size);
	if (stack_s->stack == NULL)
		return (stack_s);
	/* ------- TODO: mirar orden de llenado del stack	------- */
	/* ----The first argument should be at the top of the stack---- */
	while (argv[count + 1])
	{
		stack_s->stack[stack_s->size - count - 1] = ft_atoi(argv[count + 1]);
		count++;
	}
	return (stack_s);
}

t_data	init_data(char **argv)
{
	t_data	data;
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_a || !stack_b)
	{
		free(stack_a);
		free(stack_b);
		err_and_exit(NULL, NULL, E_NOMEM);
	}
	stack_b->stack = NULL;
	data.instr_list_head = NULL;
	stack_a = fill_stack(stack_a, argv);
	stack_b->stack = (int *)ft_calloc(sizeof(int), stack_a->size);
	stack_b->size = 0;
	data.stack_a = stack_a;
	data.stack_b = stack_b;
	if (!stack_b->stack || !stack_a->stack)
		err_and_exit(&data, NULL, E_NOMEM);
	return (data);
}
