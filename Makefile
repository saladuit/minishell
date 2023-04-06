include makerc/common.mk
include makerc/config.mk

-include $(UNIT_DEPENDS)
-include $(DEPENDS) 
-include $(MAIN_DEPENDS)

all: $(MINISHELL)

unit_test: $(UNIT_TEST)

$(MINISHELL): SHELL :=/bin/bash

$(MINISHELL): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(INCLUDE_FLAGS) -o $(MINISHELL)

$(UNIT_TEST): $(UNIT_OBJS) $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(UNIT_OBJS) $(OBJS) $(LDFLAGS) $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) $(LIBFT) -o $(UNIT_TEST)
	@./$(UNIT_TEST) -j4 $(F)

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP $(INCLUDE_FLAGS) -c $< -o $@

$(UNIT_OBJS): $(UNIT_BUILD_DIR)/%.o: $(UNIT_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

debug:
	@$(MAKE) DEBUG=1

fsan:
	@$(MAKE) FSAN=1 DEBUG=1

test:
	@$(RM) $(COVERAGE_GCDA) $(COVERAGE_FILES)
	@$(MAKE) DEBUG=1 FSAN=1 COV=1 unit_test
	@lcov -q -d build -d unit_test/build -c --output-file build/coverage.info
	@genhtml -q build/coverage.info -o build/coverage_report

analyse:
	w3m build/coverage_report/index.html

malloc_test: debug 
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) $(LIBFT) -fsanitize=undefined -rdynamic -o $@ $(INCLUDE_FLAGS) $(LDFLAGS) -L. -lmallocator

clean:
	@$(RM) $(BUILD_DIR) $(UNIT_BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(MINISHELL) $(UNIT_TEST)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

resan: fclean fsan

rebug: fclean debug

test_re: fclean test

bonus: all

.PHONY: all clean fclean re bonus
.PHONY: malloc_test
.PHONY: test test_re analyse
.PHONY: debug rebug fsan resan
