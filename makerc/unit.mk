UNIT_TEST			=test.out
UNIT_SRCS			=expand_cases.c#lexer_cases.c #tokenizer_test.c redirect_all_std.c minishell_test.c \
#					 parser_cases.c parser_test.c execute_test.c executor_cases.c

UNIT_OBJS			=$(addprefix ../$(BUILD_DIR)/, $(UNIT_SRCS:%.c=%.o))
PRODUCTION_OBJS		=$(addprefix ../, $(OBJS))

UNIT_HEADERS		=include/unit_test.h
UNIT_HEADERS		+=$(addprefix ../, $(HEADERS))

UNIT_INCLUDE_FLAGS	:=$(addprefix -I, $(sort $(dir $(UNIT_HEADERS))))
