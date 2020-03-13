NAME = RTv1
LIBPATH = ./libft
LIBNAME = -lft
SRCS_DIR = ./srcs
IDIR = ./includes
MINILIB_PATH = ./minilibx_macos
OBJS_DIR = objs
CC = gcc
CFLAGS = -Wall -Wextra -Werror
_SRCS = main.c \
		draw.c \
		init.c \
		utils.c \
		controls.c
SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))
_OBJS = $(_SRCS:%.c=%.o)
OBJS = $(addprefix $(OBJS_DIR)/, $(_OBJS))

# @say -v Fred hello, my name is Stephen Hawking, `date "+DATE: %Y-%m-%d"`

BLACK = \033[0;30m
GREEN = \033[0;32m
RED = \033[0;31m
BLINK = \033[5m
RESET = \033[0m

all: $(NAME)
	@say -v Fred $(NAME) was created
	@echo "\n$(NAME): $(GREEN)$(NAME) was created"

$(NAME): $(OBJS)
	@make -C $(LIBPATH)
	@$(CC) $(OBJS) -o $(NAME) $(CFLAGS) -L$(LIBPATH) $(LIBNAME) -L$(MINILIB_PATH) -lmlx -framework OpenGL -framework AppKit

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c includes/key.h includes/rtv1.h
	@mkdir -p objs
	@echo "$(GREEN).$(RESET)\c"
	@$(CC) -c -o $@ $< $(CFLAGS) -I$(IDIR) -I$(LIBPATH) -I$(MINILIB_PATH)

clean:
	@say -v Fred Go then, there are other worlds than these.
	@rm -f $(OBJS)
	@rmdir $(OBJS_DIR)
	@make -C $(LIBPATH) fclean
	@echo "$(GREEN).$(RESET)\c"
	@echo "\n$(NAME): $(RED)$(NAME) was clean$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBPATH) fclean

re: fclean all

.PHONY: all clean fclean re
