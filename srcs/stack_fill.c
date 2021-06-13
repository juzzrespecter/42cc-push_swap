#include "push_swap.h"

static int	stack_empty_val(char *stack_n)
{
	int	index;

	index = 0;
	while (stack_n[index] && stack_n[index] == ' ')
		index++;
	return (!stack_n[index]);
}

static t_stack_list	*stack_list_get(char **argv)
{
	t_stack_list	*l_head;
	t_stack_list	*l_node;
	int				index;

	index = 0;
	l_head = NULL;
	while (argv[index])
	{
		if (!stack_empty_val(argv[index]))
		{
			l_node = (t_stack_list *)malloc(sizeof(t_stack_list) * 1);
			ft_bzero(l_node, sizeof(t_stack_list));
			l_node->stack_n = ft_atoi(argv[index]);
			ft_lstadd_back((t_list **)&l_head, (t_list *)l_node);
		}
		index++;
	}
	return (l_head);
}

static void	stack_list_del(t_stack_list *l_head)
{
	t_stack_list	*aux_node;

	while (l_head)
	{
		aux_node = l_head->next;
		free(l_head);
		l_head = aux_node;
	}
}

static int	stack_size_get(char **argv)
{
	int	index;
	int	stack_size;

	index = 0;
	stack_size = 0;
	while (argv[index])
	{
		if (!stack_empty_val(argv[index]))
			stack_size++;
		index++;
	}
	return (stack_size);
}

t_stack	stack_fill(int start, char **argv)
{
	int				i;
	t_stack			stack;
	t_stack_list	*stack_list;

	i = 0;
	stack_list = stack_list_get(argv + start);
	stack.size = stack_size_get(argv + start);
	stack.array = (int *)malloc(sizeof(int) * stack.size);
	if (stack.array == NULL || stack_list == NULL)
		err_and_exit(NULL, NULL, E_NOMEM);
	while (stack_list)
	{
		stack.array[stack.size - (i + 1)] = stack_list->stack_n;
		stack_list = stack_list->next;
		i++;
	}
	stack_list_del(stack_list);
	return (stack);
}
