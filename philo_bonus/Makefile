SRC = create_philos.c error_check.c monitor.c \
		routine.c lst.c philosophers.c utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = philo_bonus

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(OBJ) $(CFLAGS) -o $(NAME) 

%.o : %.c philosophers.h
	cc $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all