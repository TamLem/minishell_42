/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:03:11 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/09 18:46:45 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define RESET 'y'
# define NO_RESET 'n'
# define PLACE_HOLDER 0x1D

# include <stdbool.h>

typedef struct s_token
{
	char			*value;
	int				type;
	bool			split;
	bool			error;
	bool			expanded;
	struct s_token	*next;
}		t_token;

enum e_IFS{
	WWSPACE=' ',
	WTAB='\t',
	WNEWLINE='\n',
};

enum e_OPERATORS{
	LESS='<',
	DLESS=15420,
	PIPE='|',
	GREAT='>',
	DGREAT=15934,
	ASSIGN='=',
};

enum e_grammer{
	WORD=-1,
	REDIR=8995,
	QMARK='?',
};

enum e_TOKENS{
	TOKEN=-2,
	OPERATOR=-3,
	ERROR=-9,
	FLAG='-',
	QUOTE='\'',
	DQUOTE='\"',
	IO_NUMBER=-2,
	DOLLAR='$',
} TOKENS;

enum	e_STATE{
	INQUOTE,
	OUTQUOTE,
	INDQUOTE,
	OUTDQUOTE,
};

int		lex(char *line);
bool	is_wspace(char c);
bool	is_operator(char c);
int		quotes_matched(char *line);
bool	shall_split(char *line, char *appended, int state);
int		get_state(char pos);
int		param_expand(void);
char	*field_split(char *str);
void	del_empty_tokens(void);
void	print_tokens(void);
char	*ft_strjoin_withnull(char *s1, char *s2);

#endif
