include ../makerc/colours.mk
include ../makerc/config.mk
include ../makerc/unit.mk

NAME			:= ../$(UNIT_TEST)


ifeq ($(shell uname -s), Linux)
	LDFLAGS		=-lcriterion -lreadline
else
	LDFLAGS	=-L $(shell brew --prefix readline)/lib -lcriterion -lreadline
endif

# ifeq ($(shell uname),Linux)
# 	ifeq ($(shell lsb_release -is),Ubuntu)
# 	UBUNTU = -I /usr/local/include/
# endif
# endif

all: $(NAME)
$(NAME): SHELL := /bin/bash

$(NAME): $(UNIT_OBJS) $(PRODUCTION_OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(UNIT_INCLUDE_FLAGS) ../$(LIBFT) -o $(NAME)

$(UNIT_OBJS): ../$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< $(UNIT_INCLUDE_FLAGS) $(UBUNTU) -lcriterion -o $@

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
