# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    unit.mk                                         |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2022/07/16 22:37:05 by safoh        /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2022/09/16 10:31:29 by safoh        \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

UNIT_TEST			=mini_test
UNIT_SRCS			=unit_test.c redirect_all_std.c minishell_test.c

UNIT_OBJS			=$(addprefix ../$(BUILD_DIR)/, $(UNIT_SRCS:%.c=%.o))
PRODUCTION_OBJS		=$(addprefix ../, $(OBJS))

UNIT_LIBS			=$(addprefix ../, $(LIBFT))

UNIT_HEADERS		:=include/unit_test.h \
					  ../libs/libft/include/libft.h \
					  ../libs/libft/include/get_next_line.h \
					  ../libs/libft/include/ft_printf.h \
				 $(INCLUDE_DIR)/minishell.h \
				 $(INCLUDE_DIR)/executor.h \
				 $(INCLUDE_DIR)/expander.h \
				 $(INCLUDE_DIR)/lexer.h \
				 $(INCLUDE_DIR)/parser.h \
				 $(INCLUDE_DIR)/message.h \
				 $(INCLUDE_DIR)/ft_tree.h \
					$(READLINE_INCLUDE_DIR)/readline.h

UNIT_INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(UNIT_HEADERS))))
