#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "libft.h"

# define E_DUPL 0 
# define E_NOARG 1
# define E_NONUM 2
# define E_INTOVF 3
# define E_NOMEM 4
# define E_NOINSTR 5 

# define V_FLAG 0
# define R_FLAG 1
# define C_FLAG 2

# define SWAP_ID 0
# define PUSH_ID 1 
# define ROT_ID 2
# define RROT_ID 3

# define STACK_ID_A 0
# define STACK_ID_B 1
# define STACK_ID_BOTH 2

# define SMALL_LIMIT 30 

typedef struct s_instr
{
	int	P1;
	int	C1;
	int	C2;
	int	fp;
	int	fc;
	int	next;
}				t_instr;

typedef struct s_stack
{
	int	*array;
	int	size;
}				t_stack;

typedef struct s_data
{
	t_stack		stack[2];
	t_list		*instr_list_head;
	int			n_steps;
	int			n_ins;
}				t_data;

void	swap(int stack_id, t_data *data);
void	push(int stack_id, t_data *data);
void	rotate(int stack_id, t_data *data);
void	rev_rotate(int stack_id, t_data *data);

void	free_data(t_data *data);
void	err_and_exit(t_data *data, char *err_token, int err_code);
t_data	stack_data_init(t_list *argv_lst);
t_list	*parse_element_list(char **argv);
void	parse_element_recursive(int stack_size, t_list *lst_h, t_list *lst_n);
void	exec_instr_loop(int instr_id, int stack_id, int n, t_data *data);
void	exec_instr(int instr_id, int stack_id, t_data *data);
int		stack_ud(t_stack stack_s, int pos);
void	print_instr_loop(t_data *data);
void	save_instr_init(char *instr, int instr_id, int stack_id, t_data *data);

void	sort_start(t_data *data);
int		check_if_sorted(t_stack stack, int rec);
int		**heap_sort(int **heap, int heap_size);
int		**get_index_table(int *array, int stack_size);
void	free_table(int **index_table, int table_size);
void	selection_sort(t_data *data, int id);
void	selection_sort_catcher(t_data *data, t_instr instr_set, int id);

int		next_upper_half(int pivot_min, int pivot_max, t_stack stack);
int		next_lower_half(int pivot_min, int pivot_max, t_stack stack);
int		next_catcher(int n_to_push, int id, t_data *data);
void	sort_three(t_data *data, t_stack stack);

t_list	*rotate_mgmt(t_list *instr_node);
void	print_instr(int instr_id, int stack_id);
#endif
