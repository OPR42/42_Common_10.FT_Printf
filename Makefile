NAME = libftprintf.a

INCDIR = .

SOURCES = \
			ft_printf.c \
			ft_printf_convert1.c \
			ft_printf_convert2.c \
			ft_printf_convert3.c \
			ft_printf_convert4.c \
			ft_printf_parse.c \
			ft_printf_utils.c \
			ft_printf_write.c

OBJECTS = $(SOURCES:.c=.o)

FLAGS =	-Wall -Werror -Wextra

all:	$(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

bonus:	$(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c
	cc $(FLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	clean fclean re