SRCS			=minishell.c \
				 lexer/lexer.c \
				 parser/parser.c \
				 redir.c \
				 ast.c \
				 command.c \
				 command_table.c \
				 expander/expander.c \
				 executor/executor.c \
				 executor/execute_utils.c \
				 message.c \
				 signal_handler.c \
				 utils/ft_isredir.c \
				 utils/ft_isdelimiter.c \
				 utils/ft_ismetachar.c \
				 ft_tree.c \
				 builtins/echo.c \
				 builtins/cd.c \
				 builtins/pwd.c \
				 builtins/export.c \
				 builtins/unset.c \
				 builtins/env.c \
				 builtins/exit.c \

MAIN 			:=main.c

SRC_DIR			:=src
INCLUDE_DIR		:=include
BUILD_DIR		:=build
UNIT_DIR		:=unit_test
LIB_DIR			:=libs
LIBFT_DIR		:=$(LIB_DIR)/libft
READLINE_DIR	:=$(LIB_DIR)/readline
UNIT_INCLUDE_DIR	:=$(UNIT_DIR)/$(INCLUDE_DIR)
LIBFT_INCLUDE_DIR	:=$(LIBFT_DIR)/$(INCLUDE_DIR)
READLINE_INCLUDE_DIR	:=$(READLINE_DIR)/$(INCLUDE_DIR)


OBJS			=$(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
MAIN_OBJ		=$(addprefix $(BUILD_DIR)/, $(MAIN:%.c=%.o))

HEADERS			=$(LIBFT_INCLUDE_DIR)/libft.h \
				$(INCLUDE_DIR)/minishell.h \
				$(INCLUDE_DIR)/executor.h \
				$(INCLUDE_DIR)/builtins.h \
				$(INCLUDE_DIR)/expander.h \
				$(INCLUDE_DIR)/lexer.h \
				$(INCLUDE_DIR)/parser.h \
				$(INCLUDE_DIR)/redir.h \
				$(INCLUDE_DIR)/ast.h \
				$(INCLUDE_DIR)/command.h \
				$(INCLUDE_DIR)/command_table.h \
				$(INCLUDE_DIR)/message.h \
				$(INCLUDE_DIR)/minitype.h \
				$(INCLUDE_DIR)/ft_tree.h \
				$(READLINE_INCLUDE_DIR)/readline.h

INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(HEADERS))))

LIBFT			:=$(LIBFT_DIR)/libft.a

COVERAGE		=$(SRCS:.c=.gcda) \
				$(SRCS:.c=.gcno) \
				$(UNIT_SRCS:.c=.gcno) \
				$(UNIT_SRCS:.c=.gcda)
