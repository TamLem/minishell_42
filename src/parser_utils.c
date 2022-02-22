/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:39:24 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/22 15:35:42 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../include/minishell.h"

bool	is_io_modifier(int	type)
{
	if (type == LESS || type == DLESS 
				|| type == GREAT || type == DGREAT)
		return (true);
	return (false);
}

int	check_grammer(t_simple_cmd *cmd)
{
	int		i;
	t_token	*token;
	
	i = 0;
	token = &g_data.tokens;
	while (token)
	{
		if (i = 0 && token->type != WORD && token->type !=  !is_io_modifier(token->type))
			return (2);
		token = token->next;
		/* code */
	}
	
	return (0);
}