/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:16:00 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/11 15:45:22 by tlemma           ###   ########.fr       */
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

typedef struct s_data
{
	t_token			*tokens;
	t_simple_cmd	*cmds;
	char			**env;
	t_env_list		*env_list;
	int				state;
	int				exit_status;
	int				rl_redisplay;
	void			*mem_alloced;
	int				malloc_count;
	int				n_heredocs;
}	t_data;

typedef struct s_mem_alloc
{
	long				address;
	struct s_mem_alloc	*next;
}				t_mem_alloc;

t_data	g_data;
void		free_dp(char **i);
char		*ft_append_char(char *s1, char c);
int			init_env(int argc, char **argv, char **envp);
void		*ft_malloc(size_t size);
void		mem_free_all(void);
int			check_syntax(void);
int			is_valid_name(char *argv);
int			err_handle(int error_code, char *prog, char *error_input);
char		*ft_getenv(char *name);
t_env_list	*ft_getenv_list(char *name);
char		**env_to_arr(void);
void		free_to_null(void *addr);
int			is_redir(t_token *token);
void		sig_ctrlc(int sig);
int			change_ctrlc_sym(bool value);
char		*prompt(void);
int			bashify_exit_status(void);
char		*expand_single(char *init_token,
				int var_pos, char *var, bool split);
bool		is_io_modifier(int type);

#endif