include makerc/colours.mk
include makerc/config.mk

################################################################################

NAME			:=minishell.out

CC				:=gcc
RM				:=rm -rfv
CFLAGS			=-Wall -Wextra -Werror
CFLAGS			+=$(if $(DEBUG),-g -D DEBUG)
CFLAGS			+=$(if $(FSAN),-g -D DEBUG -fsanitize=address)

LIB_FLAGS 		+=-L $(shell brew --prefix readline)/lib -l readline

################################################################################

all: $(NAME)

$(NAME): SHELL :=/bin/bash

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LIB_FLAGS) $^ $(INCLUDE_FLAGS) -o $(NAME)
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
################################################################################

clean:
	@$(RM) $(OBJS) $(MAIN_OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean
	@$(MAKE)

debug:
	@$(MAKE) DEBUG=1

rebug: fclean
	@$(MAKE) debug

fsan:
	@$(MAKE) FSAN=1

resan: fclean
	@$(MAKE) fsan

bonus: all

re_malloc_test: fclean
	@$(MAKE) malloc_test

malloc_test: $(OBJS) $(MAIN_OBJ) $(LIBFT)
	@$(MAKE) DEBUG=1
	$(CC) $(CFLAGS) $^ -fsanitize=undefined -rdynamic -o $@ $(INCLUDE_FLAGS) -L../ft_mallocator -lmallocator

valgrind: debug ## Launch valgrind
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re debug rebug valgrind malloc_test re_malloc_test fsan resan

################################################################################
