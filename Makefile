include makerc/common.mk
include makerc/config.mk

all: $(MINISHELL)

$(MINISHELL): SHELL :=/bin/bash

$(MINISHELL): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(INCLUDE_FLAGS) -o $(MINISHELL)

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(UNIT_OBJS): $(UNIT_BUILD_DIR)/%.o: $(UNIT_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(BUILD_DIR) $(UNIT_BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(MINISHELL) $(UNIT_TEST)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

bonus: all

debug:
	@$(MAKE) DEBUG=1

rebug: fclean debug

fsan:
	@$(MAKE) FSAN=1 DEBUG=1

resan: fclean fsan

unit_test: $(UNIT_TEST)

$(UNIT_TEST): $(UNIT_OBJS) $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(UNIT_OBJS) $(OBJS) $(LDFLAGS) $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) $(LIBFT) -o $(UNIT_TEST)

test:
	@$(MAKE) DEBUG=1 COV=1 unit_test
	@./$(UNIT_TEST) $(F)

ftest:
	@$(MAKE) DEBUG=1 FSAN=1 COV=1
	@$(MAKE) DEBUG=1 FSAN=1 COV=1 -C $(UNIT_DIR)


analyse:
	w3m build/coverage_report/index.html

test_re: fclean test

ftest_re: fclean ftest

coverage:
	@lcov -q -d build -d unit_test/build -c --output-file build/coverage.info
	@genhtml -q build/coverage.info -o build/coverage_report

malloc_test: debug 
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) -fsanitize=undefined -rdynamic -o $@ $(INCLUDE_FLAGS) $(LDFLAGS) -L. -lmallocator

valgrind: debug
	valgrind --leak-check=full ./$(MINISHELL)

.PHONY: all clean fclean re bonus
.PHONY: debug rebug fsan resan
.PHONY: valgrind malloc_test
.PHONY: test ftest test_re ftest_re covclean coverage analyse
