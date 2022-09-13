# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    config.mk                                       |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2022/07/16 21:50:54 by safoh        /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2022/09/13 17:31:12 by safoh        \___)=(___/                  #
#                                                                              #
# **************************************************************************** #


SRCS			=minishell.c lexer.c parser.c expander.c executor.c message.c
MAIN 			:=main.c

SRC_DIR			:=src
INCLUDE_DIR		:=include
BUILD_DIR		:=build
UNIT_DIR		:=unit_test
LIB_DIR			:=libs
LIBFT_DIR		:=$(LIB_DIR)/libft
READLINE_DIR	:=~/.brew/opt/readline
UNIT_INCLUDE_DIR	:=$(UNIT_DIR)/$(INCLUDE_DIR)
LIBFT_INCLUDE_DIR	:=$(LIBFT_DIR)/$(INCLUDE_DIR)
READLINE_INCLUDE_DIR	:=$(READLINE_DIR)/$(INCLUDE_DIR)


OBJS			=$(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
MAIN_OBJ		=$(addprefix $(BUILD_DIR)/, $(MAIN:%.c=%.o))

HEADERS			=$(LIBFT_INCLUDE_DIR)/libft.h \
				 $(INCLUDE_DIR)/minishell.h \
				 $(INCLUDE_DIR)/executor.h \
				 $(INCLUDE_DIR)/expander.h \
				 $(INCLUDE_DIR)/lexer.h \
				 $(INCLUDE_DIR)/parser.h \
				 $(INCLUDE_DIR)/message.h \
				 $(INCLUDE_DIR)/ft_tree.h \
					$(READLINE_INCLUDE_DIR)/readline.h
INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(HEADERS))))

LIBFT			:=$(LIBFT_DIR)/libft.a

COVERAGE		=$(SRCS:.c=.gcda) \
	$(SRCS:.c=.gcno) \
	$(UNIT_SRCS:.c=.gcno) \
	$(UNIT_SRCS:.c=.gcda)
