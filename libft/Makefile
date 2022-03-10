# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2022/03/10 15:55:28 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f

AR = ar rs

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c  ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c\
	ft_split.c ft_strchr.c ft_strdup.c ft_strndup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strcmp.c \
	ft_realloc_more.c \

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

INCS = libft.h

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

BONUS_OBJS = $(BONUS:.c=.o)

# Colors
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

$(NAME): $(SOURCES)
	@echo	$(Y)Compiling libft...;  
	@$(CC) $(CFLAGS) -c $(SOURCES)
	@$(AR) $(NAME) $(OBJECTS)
	@echo	$(G) libft created! $(X) ;

all: $(NAME)

clean:
	@$(RM) $(OBJECTS) $(BONUS_OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

bonus: 
	$(CC) $(CFLAGS) $(SOURCES) $(BONUS)
	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJS)
		
.PHONY: all clean fclean re bonus .c .o