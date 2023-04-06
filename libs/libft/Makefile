# Executable name
NAME										:=libft.a

#	Compiler
CC											:=gcc

#	Remove	command
RM											:=rm -rf

#	Compiler	flags
CFLAGS									=-Wall -Wextra -Werror

#	Directories
SRC_DIR									:=src
INCLUDE_DIR							:=include
BUILD_DIR								:=build

SRCS_DIRS								:=array ascii convert gnl lst mem message \
													misc printf put str
SRCS										:=$(foreach	dir,	$(SRCS_DIRS),	$(wildcard	$(SRC_DIR)/$(dir)/*.c))

#	Object	files
OBJS										:=$(patsubst	$(SRC_DIR)/%.c,	$(BUILD_DIR)/%.o,	$(SRCS))

#	Headers
HEADERS									=$(INCLUDE_DIR)/libft.h
INCLUDE_FLAGS						:=$(addprefix	-I,	$(sort	$(dir	$(HEADERS))))

#	Flags
ifdef	DEBUG
	CFLAGS								+=-g
endif

ifdef	FSAN
	CFLAGS								+=-fsanitize=address
endif

all: $(NAME)

$(MINISHELL): SHELL :=/bin/bash

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $^ -o $@

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean

.PHONY: clean fclean re
