CC := cc
CFLAGS := -Wall -Wextra -Werror
NAME := libftprintf.a
SOURCES := 	ft_printf.c \
			ft_put_helpers.c \
			ft_putun_base.c
HEADER := ft_printf.h

OBJECTS := $(SOURCES:.c=.o)

LIBFT_DIR := ../libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT): 
	make -C $(LIBFT_DIR)

$(NAME): $(OBJECTS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re