include ../makerc/colours.mk
include ../makerc/config.mk
include ../makerc/unit.mk

NAME			:= ../$(UNIT_TEST)


ifneq ($(shell uname -s), Linux)
LDFLAGS	=-L $(shell brew --prefix readline)/lib -lcriterion -lreadline
else
LDFLAGS		=-lcriterion -lreadline
endif

all: $(NAME)
$(NAME): SHELL := /bin/bash

$(NAME): $(UNIT_OBJS) $(PRODUCTION_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(UNIT_INCLUDE_FLAGS) $^ ../$(LIBFT) -o $(NAME)

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
