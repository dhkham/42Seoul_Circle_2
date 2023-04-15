NAME	= push_swap
NAME_BONUS	= checker
CC		= cc
CFLAG	= -Wall -Wextra -Werror
RM		= rm -f
SRCS	= main.c								\
		  main_utils.c							\
		  push_swap.c							\
		  greedy.c								\
		  dequefunctions.c						\
		  dequefunctions_2.c					\
		  command.c								\
		  command_2.c							\
		  sort.c								\
		  cases.c								\
		  greedy_2.c							\

SRCS_BONUS	= ./bonus/push_swap_bonus.c					\
		  	  ./bonus/greedy_bonus.c					\
		  	  ./bonus/dequefunctions_bonus.c			\
		  	  ./bonus/dequefunctions_2_bonus.c			\
		  	  ./bonus/command_bonus.c					\
		  	  ./bonus/command_2_bonus.c					\
		  	  ./bonus/sort_bonus.c						\
		  	  ./bonus/cases_bonus.c						\
		  	  ./bonus/greedy_2_bonus.c					\
			  ./bonus/checker_bonus.c					\
			  ./bonus/get_next_line.c					\
			  ./bonus/get_next_line_utils.c				\
			  ./bonus/main_bonus.c						\
			  ./bonus/main_utils_bonus.c				\

OBJS	= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all : $(NAME)

$(NAME) : libft/libft.a $(OBJS)
	$(CC) $(CFLAG) $(SRCS) -L./libft -lft -o $(NAME)

libft/libft.a :
	make -C libft

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean :
	make -C ./libft clean
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean : clean
	make -C ./libft fclean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : libft/libft.a $(OBJS_BONUS)
	$(CC) $(CFLAG) $(SRCS_BONUS) -L./libft -lft -o $(NAME_BONUS)

re : 
	make fclean 
	make all

 .PHONY : all clean fclean re bonus
