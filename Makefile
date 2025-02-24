SRC = create_philos.c error_check.c monitor.c routine.c lst.c \
		Philosophers.c utilc.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = Philosophers

ALL : $(NAME)

$(NAME) : $(OBJ)
	cc  $(OBJ) -o $(NAME)

%.o : %.c Philosophers.h
	cc $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all