#include "push_swap.h"

static int	rotate_mgmt_pos(t_list **instr_start, int id_1, int id_2)
{
	t_list	*instr_node;
	int		*instr_ids;
	int		pos;

	instr_node = *instr_start;
	if (!instr_node)
		return (0);
	pos = 0;
	instr_ids = (int *)instr_node->content;
	while (instr_node && instr_ids[0] == id_1 && instr_ids[1] == id_2)
	{
		pos++;
		instr_node = instr_node->next;
		if (instr_node)
			instr_ids = (int *)instr_node->content;
	}
	*instr_start = instr_node;
	return (pos);
}

static void	rotate_loop(int instr_id, int stack_id, int n_loop)
{
	int	index;

	index = 0;
	while (index < n_loop)
	{
		print_instr(instr_id, stack_id);
		index++;
	}
}

t_list	*rotate_mgmt(t_list *instr_node)
{
	t_list	*a_node;
	int		*a_ids;
	int		rot_1;
	int		rot_2;

	a_node = instr_node;
	a_ids = (int *)instr_node->content;
	rot_1 = rotate_mgmt_pos(&instr_node, a_ids[0], a_ids[1]);
	rot_2 = rotate_mgmt_pos(&instr_node, a_ids[0], !a_ids[1]);
	if (!rot_2)
		return (a_node);
	if (rot_2 > rot_1)
	{
		rotate_loop(a_ids[0], 2, rot_1);
		rotate_loop(a_ids[0], !a_ids[1], rot_2 - rot_1);
	}
	else
	{
		rotate_loop(a_ids[0], 2, rot_2);
		rotate_loop(a_ids[0], a_ids[1], rot_1 - rot_2);
	}
	return (instr_node);
}
