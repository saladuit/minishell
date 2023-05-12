# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    Makefile                                        |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2023/05/04 13:38:34 by safoh        /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2023/05/04 13:38:34 by safoh        \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

include makerc/common.mk
include makerc/config.mk

#-include $(UNIT_DEPENDS)
#-include $(DEPENDS)
#-include $(MAIN_DEPENDS)

# $(info $(UNIT_DEPENDS))
# $(info  $(DEPENDS))
# $(info $(MAIN_DEPENDS))

all: $(MINISHELL)
.PHONY: all

unit_test: $(UNIT_TEST) all
.PHONY: unit_test

$(MINISHELL): SHELL :=/bin/bash


$(MINISHELL): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(INCLUDE_FLAGS) -o $(MINISHELL)

$(UNIT_TEST): $(UNIT_OBJS) $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(UNIT_OBJS) $(OBJS) $(LDFLAGS) $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) $(LIBFT) -o $(UNIT_TEST)

$(MAIN_OBJ) $(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(UNIT_OBJS): $(UNIT_BUILD_DIR)/%.o: $(UNIT_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(UNIT_INCLUDE_FLAGS) $(INCLUDE_FLAGS) -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

debug:
	@$(MAKE) DEBUG=1 LOG=1
.PHONY: debug

fsan:
	@$(MAKE) FSAN=1 LOG=1 DEBUG=1
.PHONY: fsan

test:
	@$(MAKE) DEBUG=1 FSAN=1 unit_test
	@./$(UNIT_TEST) -j4 $(F)
.PHONY: test

coverage:
	@$(RM) $(COVERAGE_GCDA) $(COVERAGE_FILES)
	@$(MAKE) DEBUG=1 COV=1 unit_test
	@./$(UNIT_TEST) -j4 $(F)
	@lcov -q -d build -c --output-file build/coverage.info --rc lcov_branch_coverage=1
	@genhtml -q build/coverage.info -o build/coverage_report --rc genhtml_branch_coverage=1
.PHONY: coverage

analyse:
	w3m build/coverage_report/index.html
.PHONY: analyse

clean:
	@$(RM) $(BUILD_DIR) $(UNIT_BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
.PHONY: clean

fclean: clean
	@$(RM) $(MINISHELL) $(UNIT_TEST)
	@$(MAKE) fclean -C $(LIBFT_DIR)
.PHONY: fclean

re: fclean all
.PHONY: re

resan: fclean fsan
.PHONY: resan

rebug: fclean debug
.PHONY: rebug

test_re: fclean test
.PHONY: test_re

coverage_re: fclean coverage
.PHONY: coverage_re

bonus: all
.PHONY: bonus
