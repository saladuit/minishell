include makerc/colours.mk
include ../makerc/config.mk
include makerc/unit.mk

NAME			:= ../$(UNIT_TEST)

CC				:=gcc
RM				:=rm -rfv
CFLAGS			:=-Wall -Wextra -Werror$(if $(FSAN), -g -fsanitize=address)$(if $(DEBUG), -g)
UNIT_LFLAGS		:=-lcriterion -lreadline

all: $(NAME)
$(NAME): SHELL := /bin/bash

$(NAME): $(UNIT_OBJS) $(PRODUCTION_OBJS)
	$(CC) $(CFLAGS) $^ $(UNIT_LIBS) $(UNIT_LFLAGS) $(UNIT_INCLUDE_FLAGS) -o $(NAME)

$(UNIT_OBJS): ../$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(UNIT_INCLUDE_FLAGS) -c $< -o $@

clean:
	$(RM) $(UNIT_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE)

debug:
	@$(MAKE) DEBUG=1

rebug: fclean
	@$(MAKE) debug

fsan:
	@$(MAKE) FSAN=1

resan: fclean
	@$(MAKE) fsan

.PHONY: all clean fclean re debug rebug fsan resan
