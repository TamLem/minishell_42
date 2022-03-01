# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2022/03/01 13:13:06 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -Wno-unused-parameter -Wno-missing-braces -g
READLINE = -L /goinfre/tlemma/.brew/opt/readline/lib -lreadline
READLINE_INC = -I /goinfre/tlemma/.brew/opt/readline/include

RM = rm -rf
AR = ar rs

SDIR = src
SRCS = main.c lexer.c utils.c lexer_utils.c parser.c xecutor.c xecutor_utils.c env.c export.c\
		unset.c cd.c pwd.c echo.c err_handling.c env_export_utils.c \

ODIR = objs
OBJS = $(patsubst %.c, %.o, $(SRCS))

# Colors
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

LIBFT = $(MAKE) -C libft 

$(NAME): $(addprefix $(SDIR)/, $(SRCS))
	@echo 
	@mkdir -p $(ODIR)
	@echo	$(Y) Compiling minishell...; 
	@$(CC) $(CFLAGS) $(READLINE_INC) -I ./include/ -c $^
	@mv $(OBJS) $(ODIR)
	@$(LIBFT)
	@$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJS)) $(READLINE_INC) $(READLINE) libft/libft.a -o $(NAME)
	@$(MAKE) clean
	@echo	$(G) $(NAME) created!$(X)

all: $(NAME)

clean:
	@$(MAKE) -C libft clean
	@$(RM) $(ODIR)
	@echo $(ODIR) removed!

fclean: clean
	@echo Remove Object Files...
	@ $(MAKE) -C libft fclean
	@ $(RM) $(NAME)
	@echo $(NAME) removed!

re: fclean all

.PHONY: all clean fclean re bonus .c .o