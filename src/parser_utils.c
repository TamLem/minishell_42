/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:39:24 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/28 18:49:37 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

bool	is_io_modifier(int type)
{
	if (type == LESS || type == DLESS
				|| type == GREAT || type == DGREAT)
		return (true);
	return (false);
}

// int	check_grammer(t_simple_cmd *cmd)
// {
// 	int		i;
// 	t_token	*token;
	
// 	i = 0;
// 	token = &g_data.tokens;
// 	while (token)
// 	{
// 		if (i = 0 && token->type != WORD && token->type !=  !is_io_modifier(token->type))
// 			return (2);
// 		token = token->next;
// 	}
	
// 	return (0);
// } 