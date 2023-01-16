SRCS			=minishell.c \
				 lexer/lexer.c \
				 lexer/lexer_utils.c \
				 lexer/lexical_analyzer.c \
				 lexer/analyzer_checks.c \
				 parser/parser.c \
				 parser/redir.c \
				 parser/ast.c \
				 parser/command.c \
				 parser/command_table.c \
				 expander/expander.c \
				 expander/expander_utils.c \
				 expander/expand_arguments.c \
				 expander/index_utils.c \
				 expander/variable_expand.c \
				 expander/word_splitting.c \
				 executor/executor.c \
				 executor/execute_utils.c \
				 utils/message.c \
				 utils/signal.c \
				 envp/dup_envp.c \
				 types/is_delimiter.c \
				 types/is_double_quoted.c \
				 types/is_expand.c \
				 types/is_metachar.c \
				 types/is_quote.c \
				 types/is_redir.c \
				 types/is_single_quoted.c \
				 builtins/echo.c \
				 builtins/cd.c \
				 builtins/pwd.c \
				 builtins/export.c \
				 builtins/export_utils.c \
				 builtins/export_utils2.c \
				 builtins/unset.c \
				 builtins/env.c \
				 builtins/exit.c

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
				$(READLINE_INCLUDE_DIR)/readline.h \

INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(HEADERS))))

LIBFT			:=$(LIBFT_DIR)/libft.a

COVERAGE		=$(SRCS:.c=.gcda) \
				$(SRCS:.c=.gcno) \
				$(UNIT_SRCS:.c=.gcno) \
				$(UNIT_SRCS:.c=.gcda)
