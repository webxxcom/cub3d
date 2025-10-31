NAME 		= libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -O3

SRCS 		= \
			char/ft_isalpha.c char/ft_isdigit.c char/ft_isalnum.c char/ft_isascii.c char/ft_isprint.c char/ft_isspace.c \
			conversion/ft_toupper.c conversion/ft_tolower.c conversion/ft_atoi.c conversion/ft_itoa.c conversion/ft_atof.c \
			string/ft_strlen.c string/ft_strlcpy.c string/ft_strlcat.c string/ft_strncmp.c \
				string/ft_strchr.c string/ft_strrchr.c string/ft_strnstr.c string/ft_strcmp.c \
				string/ft_strdup.c string/ft_substr.c string/ft_strjoin.c string/ft_strtrim.c \
				string/ft_strmapi.c string/ft_split.c string/ft_striteri.c string/ft_putchar_fd.c \
				string/ft_putstr_fd.c string/ft_putendl_fd.c string/ft_putnbr_fd.c \
			memory/ft_memcmp.c memory/ft_memchr.c memory/ft_memset.c memory/ft_bzero.c \
				memory/ft_realloc.c memory/ft_memcpy.c memory/ft_memmove.c \
				memory/ft_calloc.c memory/ft_free_matrix.c \
			list/ft_lstnew.c list/ft_lstlast.c list/ft_lstmap.c list/ft_lstsize.c \
				list/ft_lst_free.c list/ft_lst_remove_if.c list/ft_lstadd_front.c \
				list/ft_lstadd_back.c list/ft_lstdelone.c list/ft_lstclear.c \
				list/ft_lstiter.c \
			printf/ft_printf.c printf/ft_print_ch.c printf/ft_print_str.c printf/ft_print_ptr.c \
				printf/ft_print_int.c printf/ft_print_uint.c printf/ft_print_hex.c \
			gnl/ft_get_next_line.c

OBJS		= $(SRCS:.c=.o)

INCLUDES	= -I.

AR			= ar rcs
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
