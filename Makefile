# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 18:12:02 by tlemma            #+#    #+#              #
#    Updated: 2022/04/03 16:24:14 by tlemma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 
CFLAGS = -Wall -Werror -Wextra -Wno-unused-parameter -Wno-missing-braces -g
READLINE = -L /Users/nlenoch/.brew/opt/readline/lib -lreadline
READLINE_INC = -I /Users/nlenoch/.brew/opt/readline/include

RM = rm -rf
AR = ar rs

SDIR = src
SRCS = $(SDIR)/main.c $(SDIR)/lexer/lexer.c $(SDIR)/lexer/lexer_utils.c $(SDIR)/lexer/lexer_param_expansion.c \
		$(SDIR)/lexer/lexer_utils_2.c\
		$(SDIR)/parser/parser.c $(SDIR)/parser/parser_utils.c \
		$(SDIR)/xecutor/xecutor.c $(SDIR)/xecutor/xecutor_utils.c $(SDIR)/xecutor/xecutor_utils_2.c $(SDIR)/xecutor/xec_child.c\
		$(SDIR)/builtins/unset.c $(SDIR)/builtins/cd.c $(SDIR)/builtins/pwd.c $(SDIR)/builtins/echo.c\
		$(SDIR)/builtins/env_export_utils.c $(SDIR)/builtins/exit.c $(SDIR)/builtins/env.c $(SDIR)/builtins/export.c\
		$(SDIR)/utils/signals.c $(SDIR)/utils/utils.c $(SDIR)/utils/err_handling.c \

ODIR = objs
OBJS = *.o

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

$(NAME): $(SRCS)
	@echo 
	@mkdir -p $(ODIR)
	@echo $(Y) Compiling minishell... $(X); 
	@$(CC) $(CFLAGS) $(READLINE_INC) -I ./include/ -c $^
	@mv *.o $(ODIR)
	@$(LIBFT)
	@$(CC) $(CFLAGS) $(addprefix $(ODIR)/, $(OBJS)) $(READLINE_INC) $(READLINE) libft/libft.a -o $(NAME)
	@$(MAKE) clean
	@echo $(G) $(NAME) created!$(X)

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