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
		exec_instr_loop(ids[0], ids[1], 1, data);
		instr_n = instr_n->next;
	}
}

static int	*checker_save_instr_parser(char *instr)
{
	int	*ids;

	ids = (int *)malloc(sizeof(int) * 2);
	if (ft_strlen(instr) < 3)
	{
		ids[0] = SWAP_ID * (instr[0] == 's') + \
				 PUSH_ID * (instr[0] == 'p') + \
				 ROT_ID * (instr[0] == 'r');
		ids[1] = S_A * (instr[1] == 'a') + \
				 S_B * (instr[1] == 'b') + \
				 S_BOTH * (instr[1] == 'r');
		return (ids);
	}
	ids[0] = RROT_ID;
	ids[1] = S_A * (instr[2] == 'a') + \
			 S_B * (instr[2] == 'b') + \
			 S_BOTH * (instr[2] == 'r');
	return (ids);
}

void	checker_save_instr(char *instr, t_data *data)
{
	t_list	*instr_node;
	t_list	*instr_head;
	int	*ids;

	ids = checker_save_instr_parser(instr);
	free(instr);
	if (!ids)
		err_and_exit(data, NULL, E_NOMEM);
	instr_head = data->instr_list_head;
	instr_node = ft_lstnew(ids);
	if (!instr_node)
	{
		free(ids);
		err_and_exit(data, NULL, E_NOMEM);
	}
	ft_lstadd_back(&instr_head, instr_node);
	data->instr_list_head = instr_head;
}
