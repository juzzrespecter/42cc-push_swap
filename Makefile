.PHONY:			clean fclean re all

CHECKER		= checker

PUSH_SWAP		= push_swap

SRCS_DIR		= ./srcs/

SRCS			= parse_args.c \
			  checker_utils.c \
			  checker_utils_2.c \
			  init_data.c \
			  err_and_exit.c \
			  swap.c \
			  push.c \
			  rotate.c \
			  insertion_sort.c \
			  heap_sort.c \
			  sort_utils.c \
			  quick_sort.c \
			  bonus_rand.c \
			  bonus_verbose.c \
			  bonus_verbose_utils.c \
			  bonus_save.c \
			  bonus_help.c

SRCS_BONUS		= bonus_rand.c \
			  bonus_print.c \
			  bonus_save.c

CHECKER_MAIN		= checker.c

PUSH_SWAP_MAIN		= push_swap.c

INCLUDE_DIR			= ./includes/

OBJS_DIR		= ./objs/

OBJS			= $(patsubst %.c, $(OBJS_DIR)%.o, $(SRCS))

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
	rm -f $(CHECKER) $(PUSH_SWAP)

re:			fclean all
