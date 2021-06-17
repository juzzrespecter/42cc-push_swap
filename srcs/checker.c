#include "push_swap.h"
#include <stdio.h>

	/* stack en argv
	 * 
	 * primer argumento en el top del stack
	 * no argumentos: checker stops
	 * checker recibe stack, espera instrucciones en stdin
	 * cuando todas las instrucciones han sido leidas, las ejecuta sobre el stack
	 * si stack a esta ordenado y b esta vacio, imprime ok.
	 * otro caso, imprime ko.
	 * caso de error, imprime error.
	 */

static int	checker_if_valid_instr(char *instr)
{
	int	instr_len;

	instr_len = ft_strlen(instr);
	if (instr_len == 2)
	{
		if (instr[0] == 'p' && ft_strchr("ab", instr[1]))
			return (1);
		if (instr[0] == 'r' && ft_strchr("abr", instr[1]))
			return (1);
		if (instr[0] == 's' && ft_strchr("abs", instr[1]))
			return (1);
	}
	if (instr_len == 3)
	{
		if (instr[0] != 'r' || instr[1] != 'r')
			return (0);
		if (ft_strchr("rab", instr[2]))
			return (1);
	}
	return (0);
}

static void	checker_exec_instr_loop(t_data *data)
{
	t_list	*instr_n;
	int		*ids;

	instr_n = data->instr_list_head;
	while (instr_n)
	{
		ids = (int *)instr_n->content;
		exec_instr(ids[0], ids[1], data);
		instr_n = instr_n->next;
	}
}

static void	checker_stack_res(t_data *data, char *res)
{
	ft_putstr(res);
	free_data(data);
	exit(EXIT_SUCCESS);
}

static void	checker_stack_order(t_data *data)
{
	int	i;

	i = 0;
	if (data->stack[STACK_ID_B].size != 0 || data->stack[STACK_ID_A].size == 0)
		checker_stack_res(data, "KO\n");
	while (i < data->stack[STACK_ID_A].size)
	{
		if (i > 0 && data->stack[STACK_ID_A].array[i] > \
				data->stack[STACK_ID_A].array[i - 1])
			checker_stack_res(data, "KO\n");
		i++;
	}
	checker_stack_res(data, "OK\n");
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;
	char	*instr_buffer;

	(void) argc;
	parse_element(1, 0, argv);
	data = stack_data_init(argv);
	while (1)
	{
		ret = get_next_line(STDIN_FILENO, &instr_buffer);
		if (ret == 0)
			break ;
		if (ret < 0)
			err_and_exit(NULL, NULL, E_NOMEM);
		if (!checker_if_valid_instr(instr_buffer))
			err_and_exit(&data, instr_buffer, E_NOINSTR);
		save_instr_init(instr_buffer, 0, 0, &data);
		free(instr_buffer);
	}
	free(instr_buffer);
	checker_exec_instr_loop(&data);
	checker_stack_order(&data);
	return (EXIT_SUCCESS);
}
