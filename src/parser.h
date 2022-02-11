/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:29 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/11 15:16:55 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define	PARSER_H

typedef struct s_simple_cmd
{
	char	*cmd;
	char	**args;
	void	*infile;
	void	*outfile;
	char	*next;
} 		t_simple_cmd;

int		parse(void);


#endif