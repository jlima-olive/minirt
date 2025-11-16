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

PARSE_LIB =	parse/libft/libft.a

PARSE_OBJ =	parse/obj/clean.o \
			parse/obj/precheck.o \
			parse/obj/parsing.o \
			parse/obj/parsing_utils.o \
			parse/obj/parse_ambient.o \
			parse/obj/parse_camera.o \
			parse/obj/parse_light.o \
			parse/obj/parse_sphere.o \
			parse/obj/parse_plane.o \
			parse/obj/parse_cylinder.o \
			parse/obj/attribute_check.o \
			parse/obj/attribute_parse.o

CFLAGS=		-Wall -Wextra -Werror

LMX_FLAGS=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

AR=			ar rcs

all: MLX LIBFT PARSE $(PROJ)

$(PROJ): $(PROJ).c $(NAME) minirt.h
	$(CC) $(CFLAGS) $(PROJ).c $(MLX_ARQ) $(LIBFT_ARQ) $(NAME) $(LMX_FLAGS) $(PARSE_LIB) -o $(PROJ)

$(NAME): $(OBJ_FILES) $(PARSE_OBJ)
	$(AR) $(NAME) $?

PARSE:
	$(MAKE) -C parse

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
	$(MAKE) -C parse clean

fclean:
	rm -fr $(PROJ).a $(OBJ_FILES) $(NAME) $(PROJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C parse fclean

re: fclean all

r:
	rm -fr $(PROJ).a $(OBJ_FILES) $(NAME) $(PROJ)
	make

.PHONY: re fclean clean all mini MLX LIBFT PARSE