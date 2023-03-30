MAIN 			:=main.c
SRCS			=minishell/minishell.c \
				 lexer/lexer.c \
				 lexer/lexer_utils.c \
				 lexer/lexical_analyzer.c \
				 lexer/analyzer_checks.c \
				 parser/parser.c \
				 parser/redir.c \
				 parser/argument.c \
				 parser/ast.c \
				 parser/command.c \
				 parser/command_table.c \
				 expander/expander.c \
				 expander/heredoc.c \
				 executor/executor.c \
				 executor/execute_utils.c \
				 utils/message.c \
				 utils/signal.c \
				 env/env.c \
				 env/dict.c \
				 env/pair.c \
				 types/is_pipe.c \
				 types/is_double_quote.c \
				 types/is_dollar.c \
				 types/is_redir.c \
				 types/is_single_quote.c \
				 types/is_quote.c \
				 builtins/echo.c \
				 builtins/cd.c \
				 builtins/pwd.c \
				 builtins/export.c \
				 builtins/export_utils.c \
				 builtins/export_utils2.c \
				 builtins/unset.c \
				 builtins/env.c \
				 builtins/exit.c

SRC_DIR			:=src
INCLUDE_DIR		:=include
BUILD_DIR		:=build
UNIT_DIR		:=unit_test
LIB_DIR			:=libs
LIBFT_DIR		:=$(LIB_DIR)/libft
READLINE_DIR	:=$(LIB_DIR)/readline
UNIT_INCLUDE_DIR	:=$(UNIT_DIR)/$(INCLUDE_DIR)
LIBFT_INCLUDE_DIR	:=$(LIBFT_DIR)/$(INCLUDE_DIR)

ifneq ($(shell uname -s), Linux)
READLINE_INCLUDE_DIR	:=$(shell brew --prefix readline)/include
endif

CFLAGS			=-Wall -Wextra -Werror

ifdef DEBUG
	CFLAGS			+=-g
endif

ifndef COV
	CFLAGS			+=-D DEBUG=1
endif

ifdef FSAN
		CFLAGS			+=-fsanitize=address
endif

ifdef COV
	CFLAGS			+=--coverage
endif

ifdef FILTER
	F			=--filter $(FILTER)
endif

OBJS			=$(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
MAIN_OBJ		=$(addprefix $(BUILD_DIR)/, $(MAIN:%.c=%.o))

HEADERS			=$(LIBFT_INCLUDE_DIR)/libft.h \
				$(INCLUDE_DIR)/minishell.h \
				$(READLINE_INCLUDE_DIR)/readline.h \

INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(HEADERS))))

LIBFT			:=$(LIBFT_DIR)/libft.a

COVERAGE		=$(SRCS:.c=.gcda) \
				$(SRCS:.c=.gcno) \
				$(UNIT_SRCS:.c=.gcno) \
				$(UNIT_SRCS:.c=.gcda)
