# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: safoh <safoh@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/17 00:40:12 by safoh         #+#    #+#                  #
#    Updated: 2022/09/16 14:27:18 by dritsema      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include makerc/colours.mk
include ../makerc/config.mk
include makerc/unit.mk

NAME			:= ../$(UNIT_TEST)

CC				:=gcc
RM				:=rm -rfv
CFLAGS			:=-Wall -Wextra -Werror -g
UNIT_LFLAGS		:=-lcriterion -lreadline

all: $(NAME)

$(NAME): SHELL := /bin/bash

$(NAME): $(UNIT_OBJS)
	$(CC) $(CFLAGS) $^ $(UNIT_LIBS) $(PRODUCTION_OBJS) $(UNIT_LFLAGS) $(UNIT_INCLUDE_FLAGS) -o $(NAME)

$(UNIT_OBJS): ../$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(UNIT_INCLUDE_FLAGS) -c $< -o $@

clean:
	$(RM) $(UNIT_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re
