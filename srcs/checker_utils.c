#include "push_swap.h"

int	checker_if_valid_instr(char *instr)
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
}

void	checker_exec_instr_loop(t_data *data)
{
	t_list *instr_n;
	int	*ids;

	instr_n = data->instr_list_head;
	while (instr_n)
	{
		ids = (int *)instr_n->content;
		exec_instr(ids[0], ids[1], data);
		instr_n = instr_n->next;
	}
}
