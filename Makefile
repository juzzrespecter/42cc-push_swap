.PHONY:			clean fclean re all

PUSH_SWAP		= push_swap
CHECKER			= checker

CHECKER_MAIN		= checker.c
PUSH_SWAP_MAIN		= push_swap.c
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

OBJS			= $(patsubst %.c, $(DIR_OBJS)%.o, $(SRCS))
OBJ_CHECKER		= $(patsubst %.c, $(DIR_OBJS)%.o, $(CHECKER_MAIN))
OBJ_PUSH_SWAP		= $(patsubst %.c, $(DIR_OBJS)%.o, $(PUSH_SWAP_MAIN))

LIB			= -L$(DIR_LIB) -lft

DIR_SRCS		= srcs/
DIR_OBJS		= objs/
DIR_INC			= includes/
DIR_LIB			= libft/

GCC			= gcc -Wall -Werror -Wextra

# --- graph utils ---
SRCS_N			= echo $(SRCS) | wc | awk '{print $1}'
COUNT			= 1
L_GREEN			= \e[1;31m
GREEN			= \e[0;32m
RED			= \e[0;31m
END			= \e[0m
# --- ----------- ---

all:			$(CHECKER) $(PUSH_SWAP)

$(CHECKER):		$(OBJS) $(OBJ_CHECKER)
	@make -C $(DIR_LIB)
	@echo -n "Creating $(@F)..."
	@$(GCC) -o $(CHECKER) $(OBJS) $(OBJ_CHECKER) $(LIB)
	@echo "$(GREEN)OK$(END)"

$(PUSH_SWAP):		$(OBJS) $(OBJ_PUSH_SWAP)
	@make -C $(DIR_LIB)
	@echo -n "Creating $(@F)..."
	@$(GCC) -o $(PUSH_SWAP) -g $(OBJS) $(OBJ_PUSH_SWAP) $(LIB)
	@echo "$(GREEN)OK$(END)"

$(DIR_OBJS)%.o:		$(DIR_SRCS)%.c $(DIR_INC)push_swap.h
	@$(GCC) -c $< -g -I$(DIR_INC) 
	@echo "Compiling $<...\t\t$(GREEN)[OK]$(END)"
	@mkdir -p $(DIR_OBJS)
	@mv $(@F) $(DIR_OBJS)

clean:
	make clean -C $(DIR_LIB)
	rm -rf $(DIR_OBJS)

fclean:			clean
	make fclean -C $(DIR_LIB)
	rm -f $(CHECKER) $(PUSH_SWAP) $(PUSH_SWAP_TEST)

re:			fclean all
