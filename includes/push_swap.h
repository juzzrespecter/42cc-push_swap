#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define E_DUPL 1
# define E_NOARG 2
# define E_NONUM 3
# define E_INTOVF 4
# define E_NOMEM 5
# define E_NOINSTR 6

typedef struct	s_stack
{
	int	*array;
	int	size;
}		t_stack;

typedef struct	s_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		flags[3];
	t_list	*instr_list_head;
}	t_data;

void	err_arg_check(int argc, char **argv);
t_data	init_data(char **argv);
void	err_and_exit(t_data *t_data, char *err_token, int err_code);
void	free_data(t_data *t_data);
void	exec_instr_loop(t_data *data);
void	check_stack_order(t_data *data);
void	swap(t_stack *stack_s);
void	swap_both(t_stack *stack_a, t_stack *stack_b);
void	push(t_stack *stack_push, t_stack *stack_pop);
void	rotate(t_stack *stack_s);
void	rotate_both(t_stack *stack_a, t_stack *stack_b);
void	rev_rotate(t_stack *stack_s);
void	rev_rotate_both(t_stack *stack_a, t_stack *stack_b);
void	cmp_instr_list(char *instr, t_data *data);

/*	----	test	---- */

void	printf_stack(t_stack *stack_a, t_stack *stack_b);	// to delete
void	insertion_sort(t_data *data);				// test
void	selection_sort(t_data *data);				// test
int		index_pos(t_stack *stack_s, int pos);
void	cmd_loop(t_data *data, char *cmd, int n);
void	heap_sort(t_data *data);


#endif
