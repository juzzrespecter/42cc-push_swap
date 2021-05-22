#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include "libft.h"

# define E_DUPL 1
# define E_NOARG 2
# define E_NONUM 3
# define E_INTOVF 4
# define E_NOMEM 5
# define E_NOINSTR 6
# define E_NOFLAG 7

# define V_FLAG 0
# define R_FLAG 1
# define S_FLAG 2
# define H_FLAG 3

typedef struct	s_stack
{
	int	*array;
	int	size;
}		t_stack;

typedef struct	s_print_info
{
	int	height;
	int	width;
	int	width_stack;
	char	*left_margin;
	int	padding;
	char	wall;
	char	margin;
	char	*cmd;
}		t_print_info;

typedef struct	s_data
{
	t_stack	stack_a;
	t_stack	stack_b;
	t_list	*instr_list_head;
	int		flags[4];
	char	*filename;
	t_print_info	purse;
	int	save_fd;
}	t_data;

t_data	init_data(char **argv);
void	err_and_exit(t_data *t_data, char *err_token, int err_code);
void	free_data(t_data *t_data);
void	exec_instr_loop(t_data *data);
void	print_instr_loop(t_data *data);
void	save_instr(char *instr, t_data *data);
void	check_stack_order(t_data *data);
void	swap(t_stack *stack_s);
void	swap_both(t_stack *stack_a, t_stack *stack_b);
void	push(t_stack *stack_push, t_stack *stack_pop);
void	rotate(t_stack *stack_s);
void	rotate_both(t_stack *stack_a, t_stack *stack_b);
void	rev_rotate(t_stack *stack_s);
void	rev_rotate_both(t_stack *stack_a, t_stack *stack_b);
void	cmp_instr_list(char *instr, t_data *data);

void	parse_args(int i, char **argv);
void	parse_args_checker(int i, char **argv);
void	parse_element(int i, int stack_sizee, char **argv);
void	parse_element_overflow(char *element);
void	parse_element_duplicates(int start, char **argv);

/*	----	test	---- */

void	insertion_sort(t_data *data);				// test
void	selection_sort(t_data *data);				// test
int		index_pos(t_stack stack_s, int pos);
void	exec_cmd(char *cmd, int n, t_data *data);
void	heap_sort(t_data *data);
void	print_cmd(char *cmd, t_data *data);
void	quick_sort(int part_size, t_data *data);

void	print_margin(t_print_info purse);
void	print_body(t_print_info purse, t_data *data);
void	print_instr(char *instr, int fd);
t_print_info	init_print_cmd(t_stack stack_s);
void	print_help_and_exit(void);
t_stack	fill_stack_with_rand(int start, char **argv);
int	init_savefile(char *filename);



#endif
