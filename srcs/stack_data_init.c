#include "push_swap.h"

static int	stack_size_get(t_list *stack_lst)
{
	int	stack_size;

	stack_size = 0;
	while (stack_lst)
	{
		stack_lst = stack_lst->next;
		stack_size++;
	}
	return (stack_size);
}

static t_stack	stack_fill(t_list *stack_lst)
{
	int		i;
	t_stack	stack;
	t_list	*stack_head;

	i = 0;
	stack_head = stack_lst;
	stack.size = stack_size_get(stack_lst);
	stack.array = (int *)malloc(sizeof(int) * stack.size);
	if (stack.array == NULL)
	{
		ft_lstclear(&stack_head, free);
		err_and_exit(NULL, NULL, E_NOMEM);
	}
	stack_head = stack_lst;
	while (stack_lst)
	{
		stack.array[stack.size - (i + 1)] = ft_atoi((char *)stack_lst->content);
		stack_lst = stack_lst->next;
		i++;
	}
	ft_lstclear(&stack_head, free);
	return (stack);
}

t_data	stack_data_init(t_list *argv_lst)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.stack[STACK_ID_A] = stack_fill(argv_lst);
	data.stack[STACK_ID_B].array = (int *)malloc(sizeof(int) \
			* data.stack[STACK_ID_A].size);
	if (!data.stack[STACK_ID_B].array || !data.stack[STACK_ID_A].array)
		err_and_exit(&data, NULL, E_NOMEM);
	data.n_steps = 6 + (data.stack[STACK_ID_A].size / 100) + \
				   (data.stack[STACK_ID_A].size / 200);
	data.n_ins = 1 + (data.stack[STACK_ID_A].size > SMALL_LIMIT) + \
				 (data.stack[STACK_ID_A].size > 300);
	return (data);
}
