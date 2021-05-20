#include "push_swap.h"

static int	get_stack_width(t_stack stack_s)
{
	int	current;
	int	width;
	int	count;
	int	n;

	count = 0;
	width = 0;
	current = 0;
	while ((count + 1) < stack_s.size)
	{
		n = stack_s.array[count];
		if (n < 0)
			n *= -1;
		if (current < n)
			current = n;
		count++;
	}
	while (current)
	{
		width++;
		current /= 10;
	}
	return (width);
}

void	print_cmd(char *cmd, t_data *data)
{	
	pid_t	pid_print;
	char	buffer[1000]; // buscar una forma mas elegante pa hacer esto

	data->purse.cmd = cmd;
	pid_print = fork();
	if (pid_print == 0)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);	// check this
		print_ceiling(data->purse);
		print_walls(data->purse, data);
		print_ceiling(data->purse);
		ft_putstr("\n\n\n");
		print_cmd_info(cmd, data);
		ft_putstr_fd("(press ENTER to continue...)\n", STDOUT_FILENO);
		read(STDIN_FILENO, buffer, 1000);
		exit(EXIT_SUCCESS);

	}
	wait(NULL);
}

t_print_info	init_print_cmd(t_stack stack_s)
{
	t_print_info purse;

	purse.width_stack = get_stack_width(stack_s);
	purse.width = purse.width_stack + 33;
	purse.height = stack_s.size + 5;
	return (purse);
}
