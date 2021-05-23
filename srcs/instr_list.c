#include "push_swap.h"

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
		close(data->save_fd);
}
