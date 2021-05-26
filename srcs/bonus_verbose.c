#include "bonus_push_swap.h"

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

int	ft_putc(int c)
{
	ft_putchar(c);
	return ('f' + 'u' + 'c' + 'k' + 'y' + 'o' + 'u');
}

#include <stdio.h>

void	print_verbose(t_data *data)
{	
	pid_t	pid_print;
	t_bonus_table *b_table;
	t_list	*node;
	int		*ids;
	char	buffer[1];
	t_data	dummy;
	struct timespec req;

	req.tv_sec = 0;
	req.tv_nsec = 100000000;
	b_table = (t_bonus_table *)data->bonus_misc;
	node = data->instr_list_head;
	dummy.stack[0].array = (int *)malloc(sizeof(int) * b_table->stack_aux.size);
	dummy.stack[1].array = (int *)malloc(sizeof(int) * b_table->stack_aux.size);
	if (dummy.stack[0].array == 0 || dummy.stack[1].array == 0)
		err_and_exit(data, NULL, E_NOMEM);
	ft_memcpy(dummy.stack[0].array, b_table->stack_aux.array, b_table->stack_aux.size * sizeof(int));
	dummy.stack[0].size = b_table->stack_aux.size;
	dummy.stack[1].size = 0;
	pid_print = fork();
	if (pid_print == 0)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		// primera impresion
		while (node)
		{
			tputs(tgetstr("cl", NULL), 1, ft_putc);
			ids = (int *)node->content;	
			exec_instr(ids[0], ids[1], &dummy);
			ft_putstr(b_table->up_margin);
			print_margin(b_table);
			print_body(data->flags[C_FLAG], b_table, &dummy);
			print_margin(b_table);
			node = node->next;
			nanosleep(&req, NULL); // check this
		}
		ft_putstr_fd("(press ENTER to exit...)\n", STDOUT_FILENO);
		while (1)
		{
			read(STDIN_FILENO, buffer, 1);
			if (buffer[0] == '\n')
			{
				free_data(data);
				exit(EXIT_SUCCESS);
			}
		}
	}
	wait(NULL);
}

t_bonus_table	*init_bonus_table(t_stack stack_s, t_data *data)
{
	t_bonus_table *b_table;
	int	aux;

	b_table = (t_bonus_table *)malloc(sizeof(t_bonus_table) * 1);
	if (!b_table)
		err_and_exit(data, NULL, E_NOMEM);
	ft_bzero(b_table, sizeof(t_bonus_table));
	b_table->width_stack = get_stack_width(stack_s);
	b_table->left_margin = "\t\t\t";
	b_table->padding = 10;
	b_table->wall = '.';
	b_table->margin = '*';
	b_table->width = b_table->width_stack * 2 + b_table->padding * 2 + 3;
	b_table->height = stack_s.size > 15 ? stack_s.size : 15;
	b_table->up_margin = "\n\n\n\n\n";
	// copy stack a, set up stack b
	b_table->stack_aux.array = (int *)malloc(sizeof(int) * stack_s.size);
	if (b_table->stack_aux.array == 0)
		err_and_exit(data, NULL, E_NOMEM);
	ft_memcpy(b_table->stack_aux.array, stack_s.array, stack_s.size * sizeof(int));
	b_table->stack_aux.size = stack_s.size;
	if (isatty(STDIN_FILENO))
	{
		b_table->term_type = getenv("TERM");
		aux = tgetent(STDIN_FILENO, b_table->term_type);
		if (!aux)
			err_and_exit(data, NULL, E_NOMEM);
	}
	return (b_table);
}
