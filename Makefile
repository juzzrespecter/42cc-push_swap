.PHONY:			clean fclean re all

CHECKER		= checker

PUSH_SWAP		= push_swap

PUSH_SWAP_TEST = push_swap_test

SRCS_DIR		= ./srcs/

SRCS			= parse_element.c \
			  checker_utils.c \
			  init_data.c \
			  err_and_exit.c \
			  instructions.c \
			  save_instr.c \
			  utils.c \
			  sort_utils.c \
			  quick_selection_sort.c \
			 small_sort.c \
			  medium_sort.c \
			  heap_sort_pivot.c \
			  ins_sort_relative_order.c

CHECKER_MAIN		= checker.c

PUSH_SWAP_MAIN		= push_swap.c

INCLUDE_DIR			= ./includes/

OBJS_DIR		= ./objs/

OBJS			= $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))

OBJS_BONUS		= $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS_BONUS))

CHECKER_OBJ		= $(patsubst %.c, $(OBJS_DIR)%.o, $(CHECKER_MAIN))

PUSH_SWAP_OBJ		= $(patsubst %.c, $(OBJS_DIR)%.o, $(PUSH_SWAP_MAIN))

GCC			= gcc -Wall -Werror -Wextra

LIBFT_DIR		= ./libft/

LIB			= -L$(LIBFT_DIR) -lft

all:			$(CHECKER) $(PUSH_SWAP)

$(CHECKER):			$(OBJS) $(CHECKER_OBJ)
	make -C $(LIBFT_DIR)
	$(GCC) -o $(CHECKER) $(OBJS) $(CHECKER_OBJ) $(LIB)

$(PUSH_SWAP):		$(OBJS) $(PUSH_SWAP_OBJ)
	make -C $(LIBFT_DIR)
	$(GCC) -o $(PUSH_SWAP) -g $(OBJS) $(PUSH_SWAP_OBJ) $(LIB)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c $(INCLUDE_DIR)push_swap.h
	$(GCC) -c $< -g -I$(INCLUDE_DIR) 
	@mkdir -p $(OBJS_DIR)
	@mv $(@F) $(OBJS_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)

fclean:			clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(CHECKER) $(PUSH_SWAP) $(PUSH_SWAP_TEST)

re:			fclean all
