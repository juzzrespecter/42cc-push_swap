#include "bonus_push_swap.h"

static void bonus_table_vis_info(t_bonus *b_table, t_stack stack)
{
	char	*max_width_str;

	if (b_table->r_min * -1 > b_table->r_max)
		max_width_str = ft_itoa(b_table->r_min);
	else
		max_width_str = ft_itoa(b_table->r_max);
	b_table->width_stack = ft_strlen(max_width_str);
	free(max_width_str);
	b_table->left_margin = "\t\t\t";
	b_table->padding = 10;
	b_table->wall = '.';
	b_table->margin = '*';
	b_table->width = b_table->width_stack * 2 + b_table->padding * 2 + 3;
	b_table->height = 12 * (stack.size < 12) + stack.size * (stack.size >= 12);
	b_table->up_margin = "\n\n\n";
}

static void	bonus_table_copy_stack(t_bonus *b_table, t_stack stack, t_data *data)
{
	b_table->dummy.stack[S_A].array = (int *)malloc(sizeof(int) * stack.size);
	b_table->dummy.stack[S_B].array = (int *)malloc(sizeof(int) * stack.size);
	if (b_table->dummy.stack[S_A].array == 0 || b_table->dummy.stack[S_B].array == 0)
		err_and_exit(data, NULL, E_NOMEM);
	ft_memcpy(b_table->dummy.stack[S_A].array, stack.array, stack.size * sizeof(int));
	b_table->dummy.stack[S_A].size = stack.size;
	b_table->dummy.stack[S_B].size = 0;
}

static void	bonus_table_init_termcaps(t_data *data)
{
	int	ret_getent;
	char	*term_type;

	if (!isatty(STDIN_FILENO))
		err_and_exit(data, NULL, E_NOMEM);
	term_type = getenv("TERM");
	ret_getent = tgetent(STDIN_FILENO, term_type);
	if (!ret_getent)
		err_and_exit(data, NULL, E_NOMEM);
}

static void	bonus_table_stack_range(t_bonus *b_table, t_stack stack)
{
	int	i;
	int	r_min;
	int	r_max;

	i = 0;
	r_min = stack.array[i];
	r_max = r_min;
	while (i < stack.size)
	{
		if (stack.array[i] < r_min)
			r_min = stack.array[i];
		if (stack.array[i] > r_max)
			r_max = stack.array[i];
		i++;
	}
	b_table->r_max = r_max;
	b_table->r_min = r_min;
}

t_bonus	*init_bonus_table(t_stack stack, t_data *data)
{
	t_bonus *b_table;

	b_table = (t_bonus *)malloc(sizeof(t_bonus) * 1);
	if (!b_table)
		err_and_exit(data, NULL, E_NOMEM);
	ft_bzero(b_table, sizeof(t_bonus));
	bonus_table_stack_range(b_table, stack);
	bonus_table_vis_info(b_table, stack);
	bonus_table_copy_stack(b_table, stack, data);
	bonus_table_init_termcaps(data);
	return (b_table);
}
