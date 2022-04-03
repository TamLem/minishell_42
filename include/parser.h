/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:29 by tlemma            #+#    #+#             */
/*   Updated: 2022/04/03 16:25:09 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}			t_args;

typedef struct s_infiles
{
	int					value;
	char				*dlmtr;
	struct s_infiles	*next;
}			t_infiles;

typedef struct s_outfiles
{
	int					value;
	struct s_outfiles	*next;
}			t_outfiles;

typedef struct s_heredocs
{
	int					value;
	struct s_heredocs	*next;
}			t_heredocs;

typedef struct s_simple_cmd
{
	char				*cmd;
	t_args				*args;
	t_infiles			*infile;
	t_outfiles			*outfile;
	t_heredocs			*heredocs;
	bool				error;
	struct s_simple_cmd	*next;
}			t_simple_cmd;

int		parse(void);
int		add_infiles(t_infiles **infile, char *file, int mode);
int		add_outfiles(t_outfiles **outfile, char *file, int mode);
int		add_args(t_args **args, char *value);
int		init_cmd_struct(t_simple_cmd **simple_cmd);
bool	is_io_modifier(int type);

#endif