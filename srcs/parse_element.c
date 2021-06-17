#include "push_swap.h"

static void	parse_element_duplicates(int start, char **argv)
{
	char	*to_cmp;
	int		i;
	int		j;

	i = 0;
	while (argv[start + i])
	{
		j = 0;
		to_cmp = argv[start + i];
		while (j < i)
		{
			if (!ft_strncmp(to_cmp, argv[start + j], ft_strlen(to_cmp) + 1))
				err_and_exit(NULL, to_cmp, E_DUPL);
			j++;
		}
		i++;
	}
}

static void	parse_element_overflow(char *element)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (*element == '-')
		i++;
	while (*(element + i) == '0')
		i++;
	len = ft_strlen(element + i);
	if (len < 10)
		return ;
	if (len > 11)
		err_and_exit(NULL, element, E_INTOVF);
	if (len == 10 && ft_strncmp(element + i, "2147483647", len) > 0 && \
			*element != '-')
		err_and_exit(NULL, element, E_INTOVF);
	if (len == 10 && ft_strncmp(element + i, "2147483648", len) > 0)
		err_and_exit(NULL, element, E_INTOVF);
}

void	parse_element(int i, int stack_size, t_list *e_lst_head)
{
	int	count;

	count = 0;
	if (!argv[i])
	{
		if (!stack_size)
			exit(EXIT_SUCCESS);
		parse_element_duplicates(i - stack_size, (char *)e_lst_head->content);
		return ;
	}
	while (argv[i][count] == ' ' && argv[i][count])
		count++;
	if (!argv[i][count])
		parse_element(i + 1, stack_size, argv);
	if (argv[i][count] == '-')
		count++;
	while (argv[i][count])
	{
		if (!ft_isdigit(argv[i][count]))
			err_and_exit(NULL, argv[i], E_NONUM);
		count++;
	}
	parse_element_overflow(argv[i]);
	parse_element(i + 1, stack_size + 1, argv);
}

t_list	*parse_element_list(char **argv)
{
	int	i;
	t_list	*e_lst_head;
	t_list	*e_lst_node;
	char	**expanded_arg;

	i = 0;
	e_lst_head = NULL;
	while (argv[i])
	{
		expanded_arg = ft_split(argv[i]);
		while (expanded_arg[j])
		{
			e_lst_node = (t_list *)malloc(sizeof(t_list));
			e_lst_node->content = expanded_arg[j];
			ft_lstadd_back(&e_lst_head, e_lst_node);
			j++;
		}
		i++;
	}
	return (e_lst_head);
}
