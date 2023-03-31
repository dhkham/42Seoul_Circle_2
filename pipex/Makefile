NAME		= pipex
CC			= cc
CFLAG		= -Wall -Wextra -Werror
RM			= rm -f
SRCS 		= pipex.c	\
		  	  init.c	\
		  	  run_cmd.c \
		  	  utils.c \
		  	  ./get_next_line/get_next_line_bonus.c \
		  	  ./get_next_line/get_next_line_utils_bonus.c \

SRCS_BONUS  = ./bonus/pipex_bonus.c	\
		  	  ./bonus/init_bonus.c	\
			  ./bonus/run_cmd_bonus.c \
			  ./bonus/utils_bonus.c \
		  	  ./get_next_line/get_next_line_bonus.c \
		  	  ./get_next_line/get_next_line_utils_bonus.c \

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

LIB_DIR = ./libft

ifdef WITH_BONUS
	OBJECTS = $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all: $(NAME)

$(NAME) : $(OBJECTS)
	make -C $(LIB_DIR)
	$(CC) $(CFLAG) -o $(NAME) $(OBJECTS) $(LIB_DIR)/libft.a

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	make clean -C $(LIB_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIB_DIR)

bonus :
	make WITH_BONUS=1 all

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus