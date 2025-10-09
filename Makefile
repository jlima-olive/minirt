PROJ=		minirt

NAME=		${PROJ}.a

PROJ_DIR=	${PROJ}_dir

MLX_DIR=	minilibx-linux

SRC_FILES=	$(wildcard $(PROJ_DIR)/*.c)

OBJ_FILES=	$(SRC_FILES:.c=.o)

LIBFT_DIR=	my_libft

SRC_LIBFT=	$(wildcard $(LIBFT_DIR)/*.c)

OBJ_LIBFT=	$(SRC_LIBFT:.c=.o)

CC=			cc

CFLAGS=		-I/usr/include -I$(MLX_DIR) -O3 -Wall -Wextra -Werror

LMX_FLAGS=	-L$(MLX_DIR) -l$(MLX_DIR) -L/usr/lib -I$(MLX_DIR) -lXext -lX11 -lm -lz

AR=			ar rcs

all: MLX $(PROJ)

$(PROJ): $(PROJ).c
	$(CC) $(CFLAGS) $(LMX_FLAGS) -c $(PROJ).c -o $(PROJ)

# $(LIBFT_DIR)/$(LIBFT_DIR).a:
# 	$(MAKE) -C $(LIBFT_DIR)

# $(MLX_DIR)/libmlx.a:
# 	$(MAKE) -C $(MLX_DIR)

# $(MLX_DIR)/libmlx_Linux.a:
# 	$(MAKE) -C $(MLX_DIR)

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
