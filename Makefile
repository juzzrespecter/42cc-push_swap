.PHONY:			clean fclean re all

PUSH_SWAP		= push_swap
CHECKER			= checker

CHECKER_MAIN		= checker.c
PUSH_SWAP_MAIN		= push_swap_debug.c
SRCS			= parse_element.c \
			  checker_utils.c \
			  init_data.c \
			  err_and_exit.c \
			  instructions.c \
			  save_instr.c \
			  utils.c \
			  sort_utils.c \
			  heap_sort_pivot.c \
			  ins_sort_relative_order.c \
			  small_sort_debug.c \
			  medium_sort_debug.c

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
L_GREEN			= \033[92m
GREEN			= \033[32m
RED			= \033[91m
END			= \033[0m
# --- ----------- ---

all:			$(CHECKER) $(PUSH_SWAP)

$(CHECKER):		$(OBJS) $(OBJ_CHECKER)
	@make -C $(DIR_LIB) >/dev/null
	@$(GCC) -o $(CHECKER) $(OBJS) $(OBJ_CHECKER) $(LIB)
	@echo "$(L_GREEN)[OK]$(GREEN)\tCreated $(@F)$(END)"

$(PUSH_SWAP):		$(OBJS) $(OBJ_PUSH_SWAP)
	@make -C $(DIR_LIB) >/dev/null
	@$(GCC) -o $(PUSH_SWAP) -g $(OBJS) $(OBJ_PUSH_SWAP) $(LIB)
	@echo "$(L_GREEN)[OK]$(GREEN)\tCreated $(@F)$(END)"

$(DIR_OBJS)%.o:		$(DIR_SRCS)%.c $(DIR_INC)push_swap.h
	@$(GCC) -c $< -g -I$(DIR_INC) 
	@echo "$(L_GREEN)[OK]$(END)\tCompiled $<"
	@mkdir -p $(DIR_OBJS)
	@mv $(@F) $(DIR_OBJS)

clean:
	@make clean -C $(DIR_LIB)
	@rm -rf $(DIR_OBJS)
	@echo "$(RED)[RM]$(END)\tRemoved $(DIR_OBJS)"

fclean:			clean
	@make fclean -C $(DIR_LIB)
	@rm -f $(CHECKER) $(PUSH_SWAP)
	@echo "$(RED)[RM]$(END)\tRemoved $(CHECKER)"
	@echo "$(RED)[RM]$(END)\tRemoved $(PUSH_SWAP)"

re:			fclean all
