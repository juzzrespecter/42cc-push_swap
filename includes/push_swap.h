#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct	s_stack
{
	int	*stack;
	int	size;
}		t_stack;

typedef struct	s_checker_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	t_list	*instr_list_head;
}	t_checker_data;

void	err_arg_check(int argc, char **argv);
t_stack fill_stack(char **argv);
void	err_and_exit(t_checker_data *t_data);
void	free_data(t_checker_data *t_data);
void	exec_instr_loop(t_checker_data *data);
void	swap(t_stack *stack_s);
void	swap_both(t_stack *stack_a, t_stack *stack_b);
void	push(t_stack *stack_push, t_stack *stack_pop);
void	rotate(t_stack *stack_s);
void	rotate_both(t_stack *stack_a, t_stack *stack_b);
void	rev_rotate(t_stack *stack_s);
void	rev_rotate_both(t_stack *stack_a, t_stack *stack_b);

#endif
