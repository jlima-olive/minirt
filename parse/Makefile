NAME = parsing
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = srcs
OBJ_DIR = obj

SRCS =  clean.c \
		precheck.c \
		parsing.c \
		parsing_utils.c \
		parse_ambient.c \
		parse_camera.c \
		parse_light.c \
		parse_sphere.c \
		parse_plane.c \
		parse_cylinder.c \
		attribute_check.c \
		attribute_parse.c

SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

MAKE = make -C
LIBFT_PATH = libft
LIBFT = -L $(LIBFT_PATH) -lft

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) $(LIBFT_PATH) all
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) $(LIBFT_PATH) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re