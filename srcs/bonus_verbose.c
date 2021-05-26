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
	t_print_info *purse;
	t_list	*node;
	int		*ids;
	char	buffer[1];
	t_data	dummy;

	purse = (t_print_info *)data->bonus_misc;
	node = data->instr_list_head;
	ft_putstr("testtt\n");
	sleep(1);
	dummy.stack[0].array = (int *)malloc(sizeof(int) * purse->stack_aux[0].size);
	dummy.stack[1].array = (int *)malloc(sizeof(int) * purse->stack_aux[0].size);
	if (dummy.stack[0].array == 0 || dummy.stack[1].array == 0)
		err_and_exit(data, NULL, E_NOMEM);
	ft_memcpy(dummy.stack[0].array, purse->stack_aux[0].array, purse->stack_aux[0].size * sizeof(int));
	purse->stack_aux[0].size = purse->stack_aux[0].size;
	pid_print = fork();
	printf("(%d) (%d)\n", dummy.stack[0].size, dummy.stack[1].size);
	if (pid_print == 0)
	{
		//tcsetattr(STDIN_FILENO, TCSANOW, &purse->print_mode_term);
		dup2(STDERR_FILENO, STDOUT_FILENO);
		while (node)
		{
			//tputs(purse->cl, 1, ft_putc);
			// falta aire por arriba, margenes minimos dentro del cubico
			ids = (int *)node->content;	
			exec_instr(ids[0], ids[1], &dummy);
			ft_putstr(purse->up_margin);
			print_margin(purse);
			print_body(data->flags[C_FLAG], purse, &dummy);
			print_margin(purse);
			node = node->next;
			sleep(1); // check this
		}
		ft_putstr_fd("(press ENTER to exit...)\n", STDOUT_FILENO);
		while (1)
		{
			read(STDIN_FILENO, buffer, 1);
			if (buffer[0] == '\n')
			{
				tcsetattr(STDIN_FILENO, TCSANOW, &purse->original_term);
				free_data(data);
				exit(EXIT_SUCCESS);
			}
		}
	}
	wait(NULL);
}

t_print_info	*init_print_info(t_stack stack_s, t_data *data)
{
	t_print_info *purse;
	int	aux;

	purse = (t_print_info *)malloc(sizeof(t_print_info) * 1);
	if (!purse)
		err_and_exit(data, NULL, E_NOMEM);
	ft_bzero(purse, sizeof(t_print_info));
	purse->width_stack = get_stack_width(stack_s);
	purse->left_margin = "\t\t\t";
	purse->padding = 10;
	purse->wall = '.';
	purse->margin = '*';
	purse->width = purse->width_stack * 2 + purse->padding * 2 + 3;
	purse->height = stack_s.size > 15 ? stack_s.size : 15;
	purse->up_margin = "\n\n\n\n\n";
	// copy stack a, set up stack b
	purse->stack_aux[0].array = (int *)malloc(sizeof(int) * stack_s.size);
	purse->stack_aux[1].array = (int *)malloc(sizeof(int) * stack_s.size);
	if (purse->stack_aux[0].array == 0 || purse->stack_aux[1].array == 0)
		err_and_exit(data, NULL, E_NOMEM);
	ft_memcpy(purse->stack_aux[0].array, stack_s.array, stack_s.size * sizeof(int));
	purse->stack_aux[0].size = stack_s.size;
	if (isatty(STDIN_FILENO))
	{
		purse->term_type = getenv("TERM");
		aux = tgetent(STDIN_FILENO, purse->term_type);
		if (!aux)
			err_and_exit(data, NULL, E_NOMEM);
		tcgetattr(STDIN_FILENO, &purse->original_term);
		tcgetattr(STDIN_FILENO, &purse->print_mode_term);
		// aqui configurar el print_mode_term: no muestre input, reciba senyales una tras otra, no procese nada excepto enter al final
		// noncanonical , time = 0, min = 0, no echo, si isig
		//ft_bzero(&purse->print_mode_term, sizeof(struct termios));
		purse->print_mode_term.c_lflag &= ~(ECHO | ICANON);
		purse->print_mode_term.c_lflag |= ISIG;
		purse->cl = tgetstr("cl", NULL);
		purse->cr = tgetstr("cr", NULL);
	}
	return (purse);
}
