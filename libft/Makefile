SRCDIR = src/
OBJDIR = bin/
######################################################################
MANDIR = mandatory/
BONDIR = bonus/
EXTDIR = extra/
######################################################################
INCDIR = include/include_imp/
######################################################################
EXTFILES = get_next_line.c\
			ft_printf/ft_printf.c\
			ft_printf/write_buf.c\
			ft_printf/parse_flags.c\
			ft_printf/print_s.c\
			ft_printf/print_c.c\
			ft_printf/print_u.c\
			ft_printf/print_di.c\
			ft_printf/print_p.c\
			ft_printf/print_xX.c\
			ft_printf/print_percent.c\
			ft_atol.c

MANFILES = ft_isalpha.c\
			ft_isdigit.c\
			ft_isalnum.c\
			ft_isascii.c\
			ft_isprint.c\
			ft_strlen.c\
			ft_memset.c\
			ft_bzero.c\
			ft_memcpy.c\
			ft_memmove.c\
			ft_strlcpy.c\
			ft_strlcat.c\
			ft_toupper.c\
			ft_tolower.c\
			ft_strchr.c\
			ft_strrchr.c\
			ft_strncmp.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_strnstr.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_strdup.c\
			ft_substr.c\
			ft_strjoin.c\
			ft_strtrim.c\
			ft_split.c\
			ft_itoa.c\
			ft_strmapi.c\
			ft_striteri.c\
			ft_putchar_fd.c\
			ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c

BONFILES = ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c

# ft_lstdelone.c
######################################################################
BONOBJ = $(addprefix $(OBJDIR), $(addprefix $(BONDIR), $(BONFILES:.c=.o)))
MANOBJ = $(addprefix $(OBJDIR), $(addprefix $(MANDIR), $(MANFILES:.c=.o)))
EXTOBJ = $(addprefix $(OBJDIR), $(addprefix $(EXTDIR), $(EXTFILES:.c=.o)))
######################################################################
AR = ar -rc
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCPATH = -I$(INCDIR)
######################################################################
NAME = libft.a

all: $(NAME)

$(NAME): $(MANOBJ) $(BONOBJ) $(EXTOBJ)
	$(AR) $(NAME) $(MANOBJ) $(BONOBJ) $(EXTOBJ)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) $(INCPATH) $< -o $@

clean:
	rm -rf $(MANOBJ)
	rm -rf $(BONOBJ)
	rm -rf $(EXTOBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all libft clean fclean re
