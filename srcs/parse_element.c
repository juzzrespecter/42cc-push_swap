#include "push_swap.h"

static void	parser_err_and_exit(char *content, t_list *lst_h, int err_id)
{
	char	*err_token;

	err_token = ft_strdup(content);
	ft_lstclear(&lst_h, free);
	err_and_exit(NULL, err_token, err_id);
}

static void	parse_element_overflow(char *element, t_list *lst_h)
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
		parser_err_and_exit(element, lst_h, E_INTOVF);
	if (len == 10 && ft_strncmp(element + i, "2147483647", len) > 0 && \
			*element != '-')
		parser_err_and_exit(element, lst_h, E_INTOVF);
	if (len == 10 && ft_strncmp(element + i, "2147483648", len) > 0)
		parser_err_and_exit(element, lst_h, E_INTOVF);
}

static void	parse_element_duplicates(t_list *lst_h)
{
	t_list	*lst_n;
	t_list	*lst_start;
	int		count;
	int		index;

	count = 0;
	lst_n = lst_h;
	while (lst_n)
	{
		index = 0;
		lst_start = lst_h;
		while (index < count)
		{
			if (!ft_strncmp(lst_n->content, lst_start->content, \
						ft_strlen(lst_n->content) + 1))
				parser_err_and_exit(lst_n->content, lst_h, E_DUPL);
			lst_start = lst_start->next;
			index++;
		}
		lst_n = lst_n->next;
		index = 0;
		count++;
	}
}

void	parse_element_recursive(int stack_size, t_list *lst_h, t_list *lst_n)
{
	int	i;

	i = 0;
	if (!lst_n)
	{
		if (!stack_size)
			exit(EXIT_SUCCESS);
		parse_element_duplicates(lst_h);
		return ;
	}
	if (!*((char *)lst_n->content + i))
		parse_element_recursive(stack_size, lst_h, lst_n->next);
	if (*((char *)lst_n->content + i) == '-')
		i++;
	while (*((char *)lst_n->content + i))
	{
		if (!ft_isdigit(*((char *)lst_n->content + i)))
			parser_err_and_exit(lst_n->content, lst_h, E_NONUM);
		i++;
	}
	parse_element_overflow(lst_n->content, lst_h);
	parse_element_recursive(stack_size + 1, lst_h, lst_n->next);
}

t_list	*parse_element_list(char **argv)
{
	int		i;
	int		j;
	t_list	*lst_h;
	t_list	*lst_n;
	char	**expanded_arg;

	i = 1;
	lst_h = NULL;
	while (argv[i])
	{
		j = 0;
		expanded_arg = ft_split(argv[i], ' ');
		while (expanded_arg[j])
		{
			lst_n = (t_list *)malloc(sizeof(t_list));
			lst_n->content = expanded_arg[j];
			lst_n->next = NULL;
			ft_lstadd_back(&lst_h, lst_n);
			j++;
		}
		free(expanded_arg);
		i++;
	}
	return (lst_h);
}
