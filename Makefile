include makerc/colours.mk
include makerc/config.mk
include makerc/unit.mk

################################################################################

NAME			:=minishell.out

CC				:=gcc
RM				:=rm -rfv

ifeq ($(shell uname -s), Linux)
LDFLAGS 		=-lreadline
else
LDFLAGS 		=-L $(shell brew --prefix readline)/lib -lreadline
endif

################################################################################

all: $(NAME)

$(NAME): SHELL :=/bin/bash

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(INCLUDE_FLAGS) -o $(NAME)

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
################################################################################

clean: covclean
	@$(RM) $(OBJS) $(MAIN_OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(UNIT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(UNIT_DIR)

re: fclean
	@$(MAKE)

bonus: all

debug:
	@$(MAKE) DEBUG=1

rebug: fclean
	@$(MAKE) debug

fsan:
	@$(MAKE) FSAN=1

resan: fclean
	@$(MAKE) fsan

test: covclean
	@$(MAKE) DEBUG=1 COV=1
	@$(MAKE) DEBUG=1 COV=1 -C $(UNIT_DIR)
	@./$(UNIT_TEST)

ftest: covclean
	@$(MAKE) DEBUG=1 FSAN=1 COV=1
	@$(MAKE) DEBUG=1 FSAN=1 COV=1 -C $(UNIT_DIR)
	@./$(UNIT_TEST)

analyse:
	w3m build/coverage_report/index.html

test_re: fclean
	@$(MAKE) test

ftest_re: fclean
	@$(MAKE) ftest

covclean:
	find build -name "*.gc*" -type f -delete
	rm -rf build/coverage*

coverage:
	@cd build && gcov -b `find . -type f -name "*.o"`
	@cd build && lcov -q -d . -c --output-file coverage.info
	@cd build && genhtml -q coverage.info -o coverage_report

malloc_test: debug 
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) -fsanitize=undefined -rdynamic -o $@ $(INCLUDE_FLAGS) $(LDFLAGS) -L. -lmallocator

valgrind: debug
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re bonus
.PHONY: debug rebug fsan resan
.PHONY: valgrind malloc_test
.PHONY: test ftest test_re ftest_re covclean coverage analyse covclean

################################################################################
