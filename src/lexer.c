/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/02 16:50:14 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef struct token
{
	char	*value;
	char	*type;
	char	*next;
};

typedef struct s_cmd_table
{
	char	*word;
	char	**options;
	char	*infile;
	char	*outfile;
} 		t_cmd_table;

enum e_IFS{
	WSPACE=' ',
	TAB='\t',
	NEWLINE='\n',
};

enum e_TOKENS{
	WORD=-1,
	FLAG='-',
	QUOTE='\'',
	DQUOTE='\"',
	LESS='<',
	GREAT='>',
	PIPE='|',
	INFILE=-2,
	OUTFILE=-3,
	DOLLAR='$',
	QMARK='?',
	BOPEN='(',
	BCLOSE=')',
};

enum	e_STATE{
	INQUOTE,
	OUTQUOTE,
	INDQUOTE,
	OUTDQUOTE,
};

