#include "push_swap.h"

/*int		find_smaller_pos(t_stack stack, int i)
  {
  int	count;
  int	n_to_compare;
  int	pos;

  pos = 0;
  count = 0;
  n_to_compare = stack_element(stack, 0);
  while (pos < stack.size - i)
  {
  if (n_to_compare > stack_element(stack, pos))
  {
  count = pos;
  n_to_compare = stack_element(stack, pos);
  }
  pos++;
  }
  return (count);
  }

  void	selection_sort(t_data *data)
  {
  int	i;
  int	pos;

  i = 0;
  while (i < data->stack[S_A].size)
  {
  pos = find_smaller_pos(data->stack[S_A], i);
  exec_instr_loop(PUSH_ID, S_B, pos, data);
  exec_instr_loop(ROT_ID, S_A, 1, data);
  exec_instr_loop(PUSH_ID, S_A, pos, data);
  i++;
  }
  }*/

static int	find_smallest(t_stack stack)
{
	int	i;
	int	smallest;
	int	smallest_pos;

	i = 0;
	smallest = stack_element(stack, 0);
	while (i < stack.size)
	{
		if (stack_element(stack, i) < smallest)
		{
			smallest = stack_element(stack, i);
			smallest_pos = i;
		}
		i++;
	}
	return (smallest_pos);
}

static void	sort_three(t_stack stack, t_data *data) // check this
{
	int	i;
	int	biggest;
	int	biggest_pos;

	i = 0;
	biggest = stack_element(stack, 0);
	while (i < 3)
	{
		if (stack_element(stack, i) > biggest)
		{
			biggest = stack_element(stack, i);
			biggest_pos = i;
		}
		i++;
	}
	if (biggest_pos != 2)
		exec_instr_loop(ROT_ID + (biggest_pos == 1), S_A, 1, data);
	if (stack_element(stack, 0) > stack_element(stack, 1))
		exec_instr_loop(SWAP_ID, S_A, 1, data);
}

static void	selection_sort_step(t_data *data)
{
	int pos;

	if (data->stack[S_A].size == 0)
		return ;
	if (check_already_sorted(data->stack[S_A], data->stack[S_A].size))
		return ;
	if (data->stack[S_A].size == 2)
	{
		exec_instr_loop(SWAP_ID, S_A, 1, data);
		return ;
	}
	if (data->stack[S_A].size == 3)
	{
		sort_three(data->stack[S_A], data);
		return ;
	}
	pos = find_smallest(data->stack[S_A]);
	if (pos < data->stack[S_A].size / 2)
		exec_instr_loop(ROT_ID, S_A, pos, data);
	else
		exec_instr_loop(RROT_ID, S_A, data->stack[S_A].size - pos, data);
	exec_instr_loop(PUSH_ID, S_B, 1, data);
	selection_sort(data);
}

void	selection_sort(t_data *data)
{
	selection_sort_step(data);
	exec_instr_loop(PUSH_ID, S_A, data->stack[S_B].size, data);
}
