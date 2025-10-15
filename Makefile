PROJ=		minirt

NAME=		${PROJ}.a

PROJ_DIR=	${PROJ}_dir

MLX_DIR=	mlx_linux

MLX_ARQ=	$(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Linux.a

SRC_FILES=	$(wildcard $(PROJ_DIR)/*.c)

OBJ_FILES=	$(SRC_FILES:.c=.o)

LIBFT_DIR=	my_libft

LIBFT_ARQ=	jojo_libft.a

SRC_LIBFT=	$(wildcard $(LIBFT_DIR)/*.c)

OBJ_LIBFT=	$(SRC_LIBFT:.c=.o)

CC=			cc

# CFLAGS=		-Wall -Wextra -Werror

LMX_FLAGS=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

AR=			ar rcs

all: MLX LIBFT $(PROJ)

$(PROJ): $(PROJ).c $(NAME)
	$(CC) $(CFLAGS) $(PROJ).c $(MLX_ARQ) $(LIBFT_ARQ) $(NAME) $(LMX_FLAGS) -o $(PROJ)

$(NAME): $(OBJ_FILES)
	$(AR) $(NAME) $(OBJ_FILES)

LIBFT:
	$(MAKE) -C $(LIBFT_DIR)

MLX: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(MLX_DIR):
	git clone https://github.com/42paris/minilibx-linux.git mlx_linux

clean:
	rm -fr $(PROJ).a $(OBJ_FILES) $(NAME) $(PROJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -fr $(PROJ).a $(OBJ_FILES) $(NAME) $(PROJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

r:
	rm -fr $(PROJ).a $(OBJ_FILES) $(NAME) $(PROJ)
	make

.PHONY: re fclean clean all mini MLX LIBFT