#ifndef BONUS_PUSH_SWAP_H
# define BONUS_PUSH_SWAP_H

# include "push_swap.h"
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>
# include <time.h>

typedef struct	s_print_info
{
	int	height;
	int	width;
	int	width_stack;
	char	*left_margin;
	char	*up_margin;
	int	padding;
	char	wall;
	char	margin;
	struct termios original_term;
	struct termios print_mode_term;
	char	*term_type;
	char	*cl;
	char	*cr;
	t_stack	stack_aux[2];
}		t_print_info;

t_data init_data_with_flags(char **argv);
t_stack	fill_stack_with_rand(int start, char **argv);
t_print_info	*init_print_info(t_stack stack_s, t_data *data);
void	print_verbose(t_data *data);
void	print_body(int c_flag, t_print_info *purse, t_data *dummy);
void	print_margin(t_print_info *purse);
int	ft_putc(int c);

# endif
