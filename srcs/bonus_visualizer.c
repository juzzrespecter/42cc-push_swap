#include "bonus_push_swap.h"

static void	print_visualizer_sleep_setup(int range, struct timespec *req)
{
	req->tv_sec = 0;
	req->tv_nsec = MAX_SLEEP - (range * STEP_SLEEP);
	if (req->tv_nsec < MIN_SLEEP)
		req->tv_nsec = MIN_SLEEP;
}

static void	print_visualizer_wait(char *msg)
{
	char	wait_buffer[1];

	ft_putstr("(press ENTER to ");
	ft_putstr(msg);
	ft_putstr("...)\n");
	while (1)
	{
		read(STDIN_FILENO, wait_buffer, 1);
		if (wait_buffer[0] == '\n')
			return ;
	}
}

static void	print_visualizer_exec(t_list *node, t_data *dummy)
{
	int	*ids;

	ids = (int *)node->content;
	exec_instr(ids[0], ids[1], dummy);
}

static void	print_visualizer(t_data *data)
{
	t_bonus			*b_table;
	struct timespec	req;
	t_list			*node;
	t_data			dummy;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	b_table = (t_bonus *)data->bonus_misc;
	dummy = b_table->dummy;
	node = data->instr_list_head;
	print_visualizer_sleep_setup(data->stack[S_A].size, &req);
	print_visualizer_step(b_table, data->flags[C_FLAG], &dummy);
	print_visualizer_wait("start");
	while (node)
	{
		print_visualizer_exec(node, &dummy);
		print_visualizer_step(b_table, data->flags[C_FLAG], &dummy);
		node = node->next;
		nanosleep(&req, NULL);
	}
	print_visualizer_wait("exit");
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	print_visualizer_init(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		print_visualizer(data);
	wait(NULL);
}
