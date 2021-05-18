#include "push_swap.h"

static void	get_stack_width(t_stack *stack_s)
{
	int	current;
	int	width;
	int	count;
	int	n;

	count = 0;
	width = 0;
	current = 0;
	while ((count + 1) < stack_s->size)
	{
		n = stack_s->array[count];
		n = -1 * (stack_s->array[count] < 0);
		if (current < n)
			current = n;
		count++;
	}
	while (current / 10)
		width++;
	return (width++);
}

static void print_cmd_process(t_print_info *purse, t_data *data)
{
	int	dup_out;

	dup_out = dup2(STDOUT_FILENO, STDERR_FILENO);	// check this
	/*
	 * printf ceiling * purse->width
	 * (printf wall + marg + stack_a + sep + stack_b + marg + wall) * purse->height
	 * printf floor * purse->width
	 * 
	 * printf descrp
	 * (press enter to continue...)
	 */
	exit(EXIT_SUCCESS);
}

void	print_cmd(char *cmd, t_data *data)
{	
	t_print_info purse;
	pid_t	pid_print;

	purse.width_a = get_stack_width(data->stack_a);
	purse.width_a = get_stack_width(data->stack_b);
	purse.height = data->stack_a->size;
	if (data->stack_b->size > data->stack_a->size)
		purse.height = data->stack_b->size;
	// add margins to height
	purse.width = purse.width_a + purse.width_b /* + margins */;
	purse.cmd = cmd;
	pid_print = fork();
	if (pid_print == 0)
		print_cmd_process(&purse, data);
	wait();
}
