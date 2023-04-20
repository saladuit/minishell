#	common.mk

#	Compiler
CC											:=gcc

#	Remove	command
RM											:=rm -rf

#	Compiler	flags
CFLAGS									=-Wall -Wextra -Werror

#	Directories
SRC_DIR									:=src
SRCS_DIRS								:=minishell lexer parser expander executor \
													utils env types builtins
INCLUDE_DIR							:=include
BUILD_DIR								:=build
LIB_DIR									:=libs
LIBFT_DIR								:=$(LIB_DIR)/libft
READLINE_DIR						:=$(LIB_DIR)/readline
LIBFT_INCLUDE_DIR				:=$(LIBFT_DIR)/$(INCLUDE_DIR)

#	Unit	test	Directories
UNIT_DIR								:=unit_test
UNIT_BUILD_DIR					:=$(UNIT_DIR)/$(BUILD_DIR)
UNIT_SRC_DIR						:=$(UNIT_DIR)/$(SRC_DIR)
UNIT_INCLUDE_DIR				:=$(UNIT_DIR)/$(INCLUDE_DIR)

#	Flags
ifdef	DEBUG
	CFLAGS								+=-g -MMD -MP
endif

ifdef LOG
	CFLAGS								+=-D LOG=1
endif

ifdef	COV
				CFLAGS					+=--coverage
endif

ifdef	FSAN
				CFLAGS					+=-fsanitize=address,undefined
endif

ifdef	FILTER
				F								:=--filter $(FILTER)
endif
