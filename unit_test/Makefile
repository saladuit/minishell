# **************************************************************************** #
#                                                                              #
#                                                     .--.  _                  #
#    Makefile                                        |o_o || |                 #
#                                                    |:_/ || |_ _   ___  __    #
#    By: safoh <safoh@student.codam.nl>             //   \ \ __| | | \ \/ /    #
#                                                  (|     | )|_| |_| |>  <     #
#    Created: 2022/07/17 00:40:12 by safoh        /'\_   _/`\__|\__,_/_/\_\    #
#    Updated: 2022/07/17 00:42:24 by safoh        \___)=(___/                  #
#                                                                              #
# **************************************************************************** #

include makerc/colours.mk
include ../makerc/config.mk
include makerc/unit.mk

NAME			:= ../$(UNIT_TEST)

CC				:=gcc
RM				:=rm -rfv
CFLAGS			:=-Wall -Wextra -Werror --coverage -g
UNIT_LFLAGS		:=-lcriterion

all: $(NAME)

$(NAME): SHELL := /bin/bash

$(NAME): $(UNIT_OBJS) ../$(MLX42)
	$(CC) $(CFLAGS) $^ $(UNIT_LIBS) $(PRODUCTION_OBJS) $(UNIT_LFLAGS) $(UNIT_INCLUDE_FLAGS) -lglfw -o $(NAME)

$(UNIT_OBJS): ../$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(UNIT_INCLUDE_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(UNIT_OBJS)

fclean: clean
	$(RM) $(NAME) 

re: fclean
	$(MAKE)

.PHONY: all clean fclean re
