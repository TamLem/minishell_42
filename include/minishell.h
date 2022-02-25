/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:16:00 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/24 14:42:08 by tlemma           ###   ########.fr       */
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
# include <stdbool.h>
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "xecutor.h"

typedef struct s_env_list
{
	char				*name;
	char				*value;
	bool				is_env;
	struct s_env_list	*next;
}	t_env_list;

typedef	struct s_data
{
	t_token			*tokens;
	t_simple_cmd 	*cmds;
	char			**env;
	t_env_list		*env_list;
	int				state;
	int				exit_status;
	int				rl_redisplay;
}	t_data;


t_data	g_data;
void	free_dp(char **i);
char	*ft_append_char(char *s1, char c);
int		init_env(int argc, char **argv, char **envp);
int		ft_export();


#endif