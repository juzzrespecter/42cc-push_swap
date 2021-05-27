#include "bonus_push_swap.h"
#include <stdio.h>

int	ft_putc(int c)
{
	ft_putchar(c);
	return ('f' + 'u' + 'c' + 'k' + 'y' + 'o' + 'u');
}

static void	print_visualizer_step(t_bonus_table *b_table, int c_flag, t_data *dummy)
{
	static int	steps = 0;

	tputs(tgetstr("cl", NULL), 1, ft_putc);
	ft_putstr(b_table->up_margin);
	print_margin(b_table);
	print_body(c_flag, b_table, dummy);
	print_margin(b_table);
	printf("\tnumber of steps: %d\n", steps);
	steps++;
}

static void	print_visualizer_start(void)
{
	char	wait_buffer[1];

	ft_putstr("(press ENTER to start...)\n");
	while (1)
	{
		read(STDIN_FILENO, wait_buffer, 1);
		if (wait_buffer[0] == '\n')
			return ;
	}
}

static void	print_visualizer_end(t_data *data)
{
	char	wait_buffer[1];

	ft_putstr("(press ENTER to exit...)\n");
	while (1)
	{
		read(STDIN_FILENO, wait_buffer, 1);
		if (wait_buffer[0] == '\n')
		{
			free_data(data);
			exit(EXIT_SUCCESS);
		}
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

	t_bonus_table	*b_table;
	struct timespec	req;
	t_list	*node;
	t_data	dummy;

	dup2(STDERR_FILENO, STDOUT_FILENO);
	b_table = (t_bonus_table *)data->bonus_misc;
	dummy = b_table->dummy;
	node = data->instr_list_head;
	req.tv_sec = 0;
	req.tv_nsec = 300000000 - dummy.stack[S_A].size * 10000000;
	req.tv_nsec = req.tv_nsec < 100000000 ? 100000000 : req.tv_nsec;
	printf("%d, %d\n", dummy.stack[0].size, dummy.stack[1].size);
	printf("%d, %d\n", dummy.stack[0].array[0], dummy.stack[0].array[1]);
	print_visualizer_step(b_table, data->flags[C_FLAG], &dummy);
	print_visualizer_start();
	while (node)
	{
		print_visualizer_exec(node, &dummy);
		print_visualizer_step(b_table, data->flags[C_FLAG], &dummy);
		node = node->next;
		nanosleep(&req, NULL); // check this
	}
	print_visualizer_end(data);
}

void	print_visualizer_init(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		print_visualizer(data);
	wait(NULL);
}
