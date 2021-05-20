#include "push_swap.h"

void	cmp_instr_list(char *instr, t_data *data)
{
	if (!ft_strncmp(instr, "sa", 3))
		swap(&data->stack_a);
	else if (!ft_strncmp(instr, "sb", 3))
		swap(&data->stack_b);
	else if (!ft_strncmp(instr, "ss", 3))
		swap_both(&data->stack_a, &data->stack_b);
	else if (!ft_strncmp(instr, "pa", 3))
		push(&data->stack_a, &data->stack_b);
	else if (!ft_strncmp(instr, "pb", 3))
		push(&data->stack_b, &data->stack_a);
	else if (!ft_strncmp(instr, "ra", 3))
		rotate(&data->stack_a);
	else if (!ft_strncmp(instr, "rb", 3))
		rotate(&data->stack_b);
	else if (!ft_strncmp(instr, "rr", 3))
		rotate_both(&data->stack_a, &data->stack_b);
	else if (!ft_strncmp(instr, "rra", 4))
		rev_rotate(&data->stack_a);
	else if (!ft_strncmp(instr, "rrb", 4))
		rev_rotate(&data->stack_b);
	else if (!ft_strncmp(instr, "rrr", 4))
		rev_rotate_both(&data->stack_a, &data->stack_b);
}

void	exec_instr_loop(t_data *data)
{
	t_list *instr_loop_count;

	instr_loop_count = data->instr_list_head;
	while (instr_loop_count)
	{
		cmp_instr_list((char *)instr_loop_count->content, data);
		instr_loop_count = instr_loop_count->next;	
	}
}
void	save_instr(char *instr, t_data *data)
{
	t_list	*instr_node;
	t_list	*instr_head;

	instr_head = data->instr_list_head;
	instr_node = ft_lstnew(instr);
	if (!instr_node)
	{
		free(instr);
		err_and_exit(data, NULL, E_NOMEM);
	}
	ft_lstadd_back(&instr_head, instr_node);
	data->instr_list_head = instr_head;
}

void	print_instr_loop(t_data *data)
{
	t_list *instr_loop_count;

	instr_loop_count = data->instr_list_head;
	while (instr_loop_count)
	{
		ft_putstr((char *)instr_loop_count->content);
		ft_putchar('\n');
		instr_loop_count = instr_loop_count->next;	
	}
	if (data->flags[S_FLAG])
		save_to_file(data);
}
