include makerc/colours.mk
include makerc/config.mk
include unit_test/makerc/unit.mk

################################################################################

NAME			:=minishell.out

CC				:=gcc
RM				:=rm -rfv
CFLAGS			=-Wall -Wextra -Werror
CFLAGS			+=$(if $(FSAN), -g -fsanitize=address)$(if $(DEBUG), -g)

################################################################################
all: $(NAME)

$(NAME): SHELL :=/bin/bash

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -L /Users/$(USER)/.brew/opt/readline/lib -lreadline $^ $(INCLUDE_FLAGS) -o $(NAME)
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
	@$(MAKE) clean -C $(UNIT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(UNIT_DIR)

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

mini_test: debug
	@$(MAKE) debug -C $(UNIT_DIR)
	@./$(UNIT_TEST) -j0
#	@gcov $(addprefix build/, $(SRCS)) -n -b -f -a

fsan_test: fsan
	@$(MAKE) fsan -C $(UNIT_DIR)
	@./$(UNIT_TEST) -j0
#	@gcov $(addprefix build/, $(SRCS)) -n -b -f -a

re_test: fclean
	@$(MAKE) mini_test

resan_test: fclean
	@$(MAKE) fsan_test

re_malloc_test: fclean
	@$(MAKE) malloc_test

malloc_test: $(OBJS) $(MAIN_OBJ) $(LIBFT)
	@$(MAKE) DEBUG=1
	$(CC) $(CFLAGS) $^ -fsanitize=undefined -rdynamic -o $@ $(INCLUDE_FLAGS) -L../ft_mallocator -lmallocator

valgrind: debug ## Launch valgrind
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re debug rebug valgrind malloc_test re_malloc_test fsan resan mini_test remini_test

################################################################################
