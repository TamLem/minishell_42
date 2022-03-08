/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:11 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/08 13:26:10 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	init_cmd_struct(t_simple_cmd **simple_cmd)
{
	*simple_cmd = ft_malloc(sizeof(t_simple_cmd));
	if (*simple_cmd == NULL)
		return (2);
	(*simple_cmd)->cmd = NULL;
	(*simple_cmd)->args = NULL;
	(*simple_cmd)->next = NULL;
	(*simple_cmd)->infile = NULL;
	(*simple_cmd)->outfile = NULL;
	(*simple_cmd)->heredocs = NULL;
	(*simple_cmd)->error = false;
	return (0);
}

int	parse_redir(t_simple_cmd *cmd, t_token *token)
{
	int	last_op;
	int	res;

	res = 0;
	last_op = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (is_io_modifier(token->type))
			last_op = token->type;
		if (token->type == REDIR)
		{
			if (last_op == LESS || last_op == DLESS)
			{
				if (add_infiles(&(cmd->infile), token->value, last_op) != 0)
					token->error = true;
			}
			else if (last_op == GREAT || last_op == DGREAT)
				res = add_outfiles(&(cmd->outfile), token->value, last_op);
			last_op = 0;
		}
		token = token->next;
	}
	return (0);
}

int	parse(void)
{
	t_token			*token;
	t_simple_cmd	*simple_cmd;

	token = g_data.tokens;
	init_cmd_struct(&(g_data.cmds));
	simple_cmd = g_data.cmds;
	while (token && !parse_redir(simple_cmd, token))
	{
		while (token && token->type != PIPE)
		{
			if (token->error)
				simple_cmd->error = true;
			if (token->type == WORD && simple_cmd->cmd == NULL)
				simple_cmd->cmd = token->value;
			if (token->type == WORD)
				add_args(&(simple_cmd->args), token->value);
			token = token->next;
		}
		if (!token || token->error)
			break ;
		init_cmd_struct(&(simple_cmd->next));
		simple_cmd = simple_cmd->next;
		token = token->next;
	}
	return (0);
}
