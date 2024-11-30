NAME = fdf

CFLAGS = -Wall -Wextra -Werror

SOURCES = 	fdf.c \
			manage_environment.c \
			drawing.c \
			map_to_coord.c
OBJECTS = $(SOURCES:.c=.o)
HEADER = fdf.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF= $(FT_PRINTF_DIR)/libftprintf.a

#MLX_FLAGS = -lmlx -lXext -lX11
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
#MLX_DIR = minilibx-linux 
MLX_DIR = minilibx_macos
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME) : $(OBJECTS) $(MLX) $(LIBFT) $(FT_PRINTF)
	cc $(CFLAGS) $(OBJECTS) -L$(MLX_DIR) -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) $(MLX_FLAGS) -lftprintf -lft -o $(NAME)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FT_PRINTF): $(LIBFT)
	make -C $(FT_PRINTF_DIR)

$(MLX) :
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(FT_PRINTF_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re