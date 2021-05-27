#ifndef BONUS_PUSH_SWAP_H
# define BONUS_PUSH_SWAP_H

# include "push_swap.h"
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>
# include <time.h>

# define MAX_SLEEP 300000000
# define STEP_SLEEP 5000000
# define MIN_SLEEP 100000000

typedef struct	s_bonus
{
	int	height;
	int	width;
	int	width_stack;
	char	*left_margin;
	char	*up_margin;
	int	padding;
	char	wall;
	char	margin;
	int		r_max;
	int		r_min;
	t_data	dummy;
}		t_bonus;

t_data init_data_with_flags(char **argv);
t_stack	fill_stack_with_rand(int start, char **argv);
t_bonus	*init_bonus_table(t_stack stack_s, t_data *data);
void	print_visualizer_step(t_bonus *b_table, int c_flag, t_data *dummy);
void	print_visualizer_init(t_data *data);
void	print_body(int c_flag, t_bonus *b_table, t_data *dummy);

# endif
