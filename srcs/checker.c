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

int	main(int argc, char **argv)
{
	t_data		data;
	int	ret;
	char	*instr_buffer;

	checker_parse_args(argc, argv);
	data = init_data(argv);
	while (1)
	{
		ret = get_next_line(STDIN_FILENO, &instr_buffer);
		if (ret == 0)
			break;
		if (ret < 0)
			err_and_exit(NULL, NULL, E_NOMEM);
		if (!checker_if_valid_instr(instr_buffer))
			err_and_exit(&data, instr_buffer, E_NOINSTR);
		checker_save_instr(instr_buffer, &data);
	}
	checker_exec_instr_loop(&data);
	checker_stack_order(&data);
	return (EXIT_SUCCESS);
}
