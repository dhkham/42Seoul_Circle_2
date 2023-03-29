NAME	= pipex
CC		= cc
CFLAG	= -Wall -Wextra -Werror
RM		= rm -f
SRCS 	= pipex.c	\
		  init.c	\
		  run_cmd.c \
		  ./get_next_line/get_next_line_bonus.c \
		  ./get_next_line/get_next_line_utils_bonus.c \

OBJS	= $(SRCS:.c=.o)

LIB_DIR = ./libft

all: $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) -o $(NAME) $(OBJS) $(LIB_DIR)/libft.a

clean:
	$(RM) $(OBJS)
	make clean -C $(LIB_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re