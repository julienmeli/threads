CC = cc -Wall -Wextra -Werror
INC = -I $(HEADER)
HEADER = .
SRCDIR = .
OBJDIR = $(SRCDIR)
SRC = actions.c\
      arguments.c\
      diary.c\
      utils.c\
      initialization.c\
      main.c\
      running.c
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))
NAME = philo
LIBRARY = libphilo.a
all: $(NAME)

$(NAME): $(LIBRARY)
	$(CC) $(INC) main.c -o $(NAME) -L. -lphilo

$(LIBRARY): $(OBJS)
	ar -rcs $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIBRARY)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
