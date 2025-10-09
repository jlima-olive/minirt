PROJ=		minirt

NAME=		${PROJ}.a

PROJ_DIR=	${PROJ}_dir

SRC_FILES=	$(wildcard $(PROJ_DIR)/*.c)

OBJ_FILES=	$(SRC_FILES:.c=.o)

LIBFT_DIR=		my_libft

SRC_LIBFT=	$(wildcard $(LIBFT_DIR)/*.c)

OBJ_LIBFT=	$(SRC_LIBFT:.c=.o)

CC=			cc

CFLAGS=		-Wall -Wextra -Werror -g

AR=			ar rcs

all: $(PROJ)

$(PROJ): $(PROJ).c $(LIBFT_DIR)/$(LIBFT_DIR).a mini
	$(CC) $(CFLAGS) $(CFLAGS) -c $(PROJ).c -o $(PROJ)

$(LIBFT_DIR)/$(LIBFT_DIR).a:
	$(MAKE) -C $(LIBFT_DIR)

mini: minilibx-linux
	$(MAKE) -C $(LIBFT_DIR)

minilibx-linux:
	git clone  

clean:
	rm -fr $(PROJ).a
	rm -fr $(OBJ_FILES)
	$(MAKE) -C minilibx-linux clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	rm -fr $(PROJ).a
	rm -fr $(OBJ_FILES)
	rm -fr $(PROJ)
	$(MAKE) -C minilibx-linux clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

r:
	rm -fr $(PROJ).a
	rm -fr $(OBJ_FILES)
	make
	./minirt

.PHONY: re fclean clean all mini

# so:
