# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    Makefile                                           :+:      :+:    :+:    #
#                                                    |:_/ || |_ _   ___  __    #
#    By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2022/02/09 17:06:29 by safoh        /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2022/06/12 20:31:04 by safoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../../makerc/colours.mk
include ../../makerc/lib_makefile.mk

################################################################################
NAME			=libft.a

CC				:=gcc
RM				:=rm -rf
CFLAGS			=-Wall -Wextra -Werror $(if $(DEBUG),-g) \
					$(if $(FSAN),-fsanitize=address -g)

SRC_DIR 		:=./src
BUILD_DIR		:=./build
OBJS			=$(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
HEADERS			=include/libft.h
INCLUDE_FLAGS	=$(addprefix -I, $(sort $(dir $(HEADERS))))

################################################################################
all: $(NAME)

$(NAME): SHELL := /bin/bash

$(NAME): $(OBJS)
	@ar rc $@ $^
	@printf "$(BLUE_FG)$(NAME)$(RESET_COLOR) created\n"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(CLEAR_REST_OF_LINE)\r"

################################################################################
clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME) *.a *.dSYM

re: fclean all

debug:
	@$(MAKE) DEBUG=1

fsan:
	@$(MAKE) FSAN=1

libft_tester: re
	bash tests/libft-war-machine/grademe.sh -d -u $(FILE)

libft_unit_test: re
	$(MAKE) -C ./tests/libft-unit-test f $(FILE)
	cat -e tests/libft-unit-test/result.log

main: all
	$(CC) $(CFLAGS) src/main.c -lft_debug -o libft_gdb
	./libft_gdb

.PHONY: all clean fclean re libft_tester main fsan debug
################################################################################
