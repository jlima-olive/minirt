PROJ=		minirt

NAME=		${PROJ}.a

PROJ_DIR=	${PROJ}_dir

MLX_DIR=	minilibx-linux

MLX_ARQ=	$(MLX_DIR)/libmlx.a $(MLX_DIR)/libmlx_Linux.a

SRC_FILES=	$(wildcard $(PROJ_DIR)/*.c)

OBJ_FILES=	$(SRC_FILES:.c=.o)

LIBFT_DIR=	my_libft

LIBFT_ARQ=	jojo_libft.a

SRC_LIBFT=	$(wildcard $(LIBFT_DIR)/*.c)

OBJ_LIBFT=	$(SRC_LIBFT:.c=.o)

CC=			cc

CFLAGS=		-Wall -Wextra -Werror

LMX_FLAGS=	-Wall -Wextra -Werror -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz

#
MLBLIB=		minilibx-linux/libmlx_Linux.a

MLBMAC=		minilibx-linux/libmlx.a

LMX_FLAGS=					 -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz
#

AR=			ar rcs

all: MLX $(PROJ)

$(PROJ): $(PROJ).c $(LIBFT_ARQ) $(NAME)
	$(CC) $(LMX_FLAGS) $(MLX_ARQ) $(LIBFT_ARQ) $(NAME) $(LMX_FLAGS) $(PROJ).c -o $(PROJ)

$(NAME):
	$(AR) $(NAME) $(OBJ_FILES)

$(LIBFT_ARQ):
	$(MAKE) -C $(LIBFT_DIR)

MLX: $(MLX_DIR)
	$(MAKE) -C $(MLX_DIR)

$(MLX_DIR):
	git clone https://github.com/42paris/minilibx-linux.git

clean:
	rm -fr $(PROJ).a
	rm -fr $(OBJ_FILES)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -fr $(PROJ).a
	rm -fr $(OBJ_FILES)
	rm -fr $(PROJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

r:
	rm -fr $(PROJ).a
	rm -fr $(OBJ_FILES)
	make
	./minirt

.PHONY: re fclean clean all mini MLX
