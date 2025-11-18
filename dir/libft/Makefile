CC = cc 
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a

SRC = 	ft_strlen.c ft_strcmp.c ft_strncmp.c \
		ft_atoi.c ft_atof.c ft_isalnum.c gnl.c

OBJ = $(SRC:.c=.o)

AR = ar rcs

.PHONY: all bonus fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all