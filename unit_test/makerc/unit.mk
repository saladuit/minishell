# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    unit.mk                                            :+:    :+:             #
#                                                      +:+                     #
#    By: safoh <safoh@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/16 22:37:05 by safoh         #+#    #+#                  #
#    Updated: 2022/09/17 17:19:34 by dritsema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

UNIT_TEST			=mini_test
UNIT_SRCS			=lexer_cases.c redirect_all_std.c minishell_test.c tokenizer_test.c

UNIT_OBJS			=$(addprefix ../$(BUILD_DIR)/, $(UNIT_SRCS:%.c=%.o))
PRODUCTION_OBJS		=$(addprefix ../, $(OBJS))

UNIT_LIBS			=$(addprefix ../, $(LIBFT))

UNIT_HEADERS		:=include/unit_test.h \
					  ../libs/libft/include/libft.h \
					  ../libs/libft/include/get_next_line.h \
					  ../libs/libft/include/ft_printf.h \
				 ../$(INCLUDE_DIR)/minishell.h \
				../$(INCLUDE_DIR)/executor.h \
				../$(INCLUDE_DIR)/expander.h \
				../$(INCLUDE_DIR)/lexer.h \
				../$(INCLUDE_DIR)/parser.h \
				../$(INCLUDE_DIR)/message.h \
				../$(INCLUDE_DIR)/ft_tree.h \
					$(READLINE_INCLUDE_DIR)/readline.h

UNIT_INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(UNIT_HEADERS))))
