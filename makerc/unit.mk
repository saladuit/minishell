UNIT_TEST			=test.out
UNIT_SRCS			=builtin_cases.c expand_cases.c env_cases.c lexer_cases.c minishell_cases.c \
							 parser_cases.c types_cases.c

UNIT_OBJS			=$(addprefix ../$(BUILD_DIR)/unit_test/, $(UNIT_SRCS:%.c=%.o))
PRODUCTION_OBJS		=$(addprefix ../, $(OBJS))

UNIT_HEADERS		=include/unit_test.h
UNIT_HEADERS		+=$(addprefix ../, $(HEADERS))

UNIT_INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(UNIT_HEADERS))))
