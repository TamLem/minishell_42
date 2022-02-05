/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 13:03:11 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/05 14:57:26 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

typedef struct s_token
{
	char			*value;
	char			type;
	struct s_token	*next;
}			t_token;

typedef struct s_cmd_table
{
	char	*word;
	char	**options;
	char	*infile;
	char	*outfile;
} 		t_cmd_table;

typedef enum {false, true = !false} bool; 

enum e_IFS{
	WSPACE=' ',
	TAB='\t',
	NEWLINE='\n',
};

enum e_OPERATORS{
	LESS='<',
	DLESS=15420,
	PIPE='|',
	GREAT='>',
	DGREAT=15934,
	ASSIGN='=',
};

enum e_TOKENS{
	WORD=-1,
	TOKEN=-2,
	OPERATOR=-3,
	FLAG='-',
	QUOTE='\'',
	DQUOTE='\"',
	IO_NUMBER=-2,
	DOLLAR='$',
	QMARK='?',
} TOKENS;

enum	e_STATE{
	INQUOTE,
	OUTQUOTE,
	INDQUOTE,
	OUTDQUOTE,
};

int	lex(char *line);


#endif
