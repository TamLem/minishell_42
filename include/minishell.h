/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:16:00 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/20 17:39:36 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"
 
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../src/lexer.h"
# include "../src/parser.h"
# include "../src/xecutor.h"

typedef	struct s_data
{
	t_token			*tokens;
	t_simple_cmd 	*cmds;
	char			**env;
	int				state;
	int				exit_status;
}	t_data;

t_data	g_data;
void	free_dp(char **i);
char	*ft_append_char(char *s1, char c);

#endif