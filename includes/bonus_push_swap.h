#ifndef BONUS_PUSH_SWAP_H
# define BONUS_PUSH_SWAP_H

# include "push_swap.h"
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>
# include <time.h>

typedef struct	s_bonus_table
{
	int	height;
	int	width;
	int	width_stack;
	char	*left_margin;
	char	*up_margin;
	int	padding;
	char	wall;
	char	margin;
	t_data	dummy;
	int		r_max;
	int		r_min;
}		t_bonus_table;

t_data init_data_with_flags(char **argv);
t_stack	fill_stack_with_rand(int start, char **argv);
t_bonus_table	*init_bonus_table(t_stack stack_s, t_data *data);
void	print_visualizer_init(t_data *data);
void	print_body(int c_flag, t_bonus_table *purse, t_data *dummy);
void	print_margin(t_bonus_table *purse);
int	ft_putc(int c);

# endif
