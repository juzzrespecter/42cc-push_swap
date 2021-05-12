#include "push_swap.h"
#include <stdio.h>

static int	check_if_valid_instr(char *instr)
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
	/* strcmp sa sb ss pa pb ra rb rr rra */
}

static void	save_instr(char *instr, t_checker_data *data)
{
	t_list	*instr_node;
	t_list	*instr_head;

	instr_head = data->instr_list_head;
	instr_node = ft_lstnew(instr);
	if (!instr_node)
	{
		free(instr);
		err_and_exit(data);
	}
	ft_lstadd_back(&instr_head, instr_node);
	printf("head out: %s %p\n", (char *)instr_head->content, instr_head->next);
	data->instr_list_head = instr_head;
}

int	main(int argc, char **argv)
{
	t_checker_data		data;
	t_stack	stack_a;
	t_stack	stack_b;
	int	ret;
	char	*instr_buffer;

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

	/*func err_check_plus_atoi;
	func read_from_stdin;
	func exec_instr_loop;
	func check_stacks;

	imprime lo que proceda;*/

	/*	err check	*/
	err_arg_check(argc, argv);

	/*	fill stack	*/
	stack_a = fill_stack(argv);
	stack_b.size = 0;
	stack_b.stack = (int *)ft_calloc(sizeof(int), 1);
	data.stack_a = &stack_a;
	data.stack_b = &stack_b;
	data.instr_list_head = NULL;
	/*	instructions loop	*/
	while (1)
	{
		ret = get_next_line(STDIN_FILENO, &instr_buffer);
		if (ret == 0)
			break;
		if (ret < 0)
			err_and_exit(NULL);
		if (!check_if_valid_instr(instr_buffer))
		{
			free(instr_buffer);
			err_and_exit(&data);
		}
		save_instr(instr_buffer, &data);
		/*
		 *	func save_instr ( array? linked list? )
		 */
		printf("head main: %s %p\n", (char *)data.instr_list_head->content, data.instr_list_head->next);
		
		/*
		 *	sa
		 *	sb
		 *	ss
		 *	pa
		 *	pb
		 *	ra
		 *	rb
		 *	rr
		 *	rra
		 *	rrb
		 *	rrr
		 */
	}
	exec_instr_loop(&data);
	/*	func exec();		*/
	/*	check if success	*/



}
