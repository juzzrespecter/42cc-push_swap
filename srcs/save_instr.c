#include "push_swap.h"

static int	*checker_save_instr_parser(char *instr, int *ids)
{
	if (ft_strlen(instr) < 3)
	{
		ids[0] = SWAP_ID * (instr[0] == 's') + \
				 PUSH_ID * (instr[0] == 'p') + \
				 ROT_ID * (instr[0] == 'r');
		ids[1] = STACK_ID_A * (instr[1] == 'a') + \
				 STACK_ID_B * (instr[1] == 'b') + \
				 STACK_ID_BOTH * (instr[1] == 'r');
		return (ids);
	}
	ids[0] = RROT_ID;
	ids[1] = STACK_ID_A * (instr[2] == 'a') + \
			 STACK_ID_B * (instr[2] == 'b') + \
			 STACK_ID_BOTH * (instr[2] == 'r');
	return (ids);
}

static void	save_instr(int *ids, t_data *data)
{
	t_list	*instr_node;
	t_list	*instr_head;

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

void	save_instr_init(char *instr, int instr_id, int stack_id, t_data *data)
{
	int	*ids;

	ids = (int *)malloc(sizeof(int) * 2);
	if (!ids)
		err_and_exit(data, NULL, E_NOMEM);
	if (instr == NULL)
	{
		ids[0] = instr_id;
		ids[1] = stack_id;
	}
	else
		ids = checker_save_instr_parser(instr, ids);
	save_instr(ids, data);
}
