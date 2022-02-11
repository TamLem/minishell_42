/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:11 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/11 15:39:23 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "parser.h"

t_simple_cmd	*init_cmd(void)
{
	t_simple_cmd	*simple_cmd;

	if (g_data.cmds == NULL)
	{
		g_data.cmds = malloc(sizeof(t_simple_cmd));
		if (g_data.cmds == NULL)
			return (1);
	}
	simple_cmd = g_data.cmds;
	simple_cmd->cmd = NULL;
	simple_cmd->args = NULL;
	simple_cmd->next = NULL;

	return (0);
}

int	parse(void)
{
	t_token			*token;
	t_simple_cmd	*simple_cmd;

	g_data.cmds = NULL;
	token = &g_data.tokens;
	simple_cmd = init_cmd();
	while (token)
	{
		if (token->type == OPERATOR)
		{
			//save for later
		}
		else if (token->type == WORD && simple_cmd->cmd == NULL)
			simple_cmd->cmd = WORD;
		else if (token->type == PIPE)
		{
			//end simple cmd
		}
		else
		{
			//add to args
		}
	}
	return (0);
}