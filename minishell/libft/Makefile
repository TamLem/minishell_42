# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 15:04:31 by nlenoch           #+#    #+#              #
#    Updated: 2021/08/17 19:37:11 by nlenoch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror
RM = rm -f

#ar creates, modifies and extracts from archives
# c creates archives 
# r insers files member into archive (with replacement)
# s writes an object-file index into the archive 
AR = ar -crs

#wildcard * searches for all files with .c
SOURCES = ft_isalpha.c ft_isdigit.c ft_isascii.c ft_isprint.c \
		ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
		ft_bzero.c ft_calloc.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_strdup.c \
		ft_toupper.c ft_tolower.c ft_atoi.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_isalnum.c

#creates for all .c files a .o file
OBJECTS = $(SOURCES:.c=.o)

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c

BONUS_OBJECTS = $(BONUS:.c=.o)

#builds everything
all: $(NAME)

#creates a static library
$(NAME): $(SOURCES) libft.h
	$(CC) $(CFLAGS) $(SOURCES)
	$(AR) $(NAME) $(OBJECTS)

#removes all .o files
clean:
	$(RM) $(OBJECTS) $(BONUS_OBJECTS)

#removes all *.o files + libft.a
fclean: clean
	$(RM) $(NAME)

#removes all *.o files + libft.a and rebuild everything
re: fclean all

bonus: $(OBJECTS) $(BONUS_OBJECTS) libft.h
	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)
