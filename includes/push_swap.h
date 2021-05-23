#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include "libft.h"

# define E_DUPL 0 
# define E_NOARG 1
# define E_NONUM 2
# define E_INTOVF 3
# define E_NOMEM 4
# define E_NOFLAG 5 
# define E_NOINSTR 6

# define V_FLAG 0
# define R_FLAG 1
# define S_FLAG 2
# define H_FLAG 3

# define SWAP_ID 0
# define PUSH_ID 1 
# define ROT_ID 2
# define RROT_ID 3

# define S_A 0
# define S_B 1
# define S_BOTH 2

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
	t_stack	stack[2];
	t_list	*instr_list_head;
	int		flags[4];
	char	*filename;
	t_print_info	purse;
	int	save_fd;
}	t_data;

void	swap(int stack_id, t_data *data);
void	swap_both(int stack_id, t_data *data);
void	push(int stack_id, t_data *data);
void	rotate(int stack_id, t_data *data);
void	rotate_both(int stack_id, t_data *data);
void	rev_rotate(int stack_id, t_data *data);
void	rev_rotate_both(int stack_id, t_data *data);

void	free_data(t_data *data);
void	err_and_exit(t_data *data, char *err_token, int err_code);
t_data	init_data(char **argv);
void	parse_args(int i, char **argv);
void	parse_element(int i, int stack_size, char **argv);
void	exec_instr_loop(int instr_id, int stack_id, int n, t_data *data);
void	print_instr_loop(t_data *data);
void	print_instr(int instr_i, t_data *data);
int	stack_element(t_stack stack_s, int pos);

void	insertion_sort(t_data *data);

int		checker_if_valid_instr(char *instr);
void	checker_exec_instr_loop(t_data *data);
void	checker_save_instr(char *instr, t_data *data);
void	checker_stack_order(t_data *data);
void	checker_parse_args(int argc, char **argv);

void	print_help_and_exit(void);
t_stack	fill_stack_with_rand(int start, char **argv);
int	init_savefile(char *filename);
t_print_info	init_print_cmd(t_stack stack_s);
void	print_verbose(char *cmd, t_data *data);
void	print_margin(t_print_info purse);
void	print_body(t_print_info purse, t_data *data);

#endif
