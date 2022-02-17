/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:11 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/17 22:50:27 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "parser.h"

int	init_cmd(t_simple_cmd **simple_cmd)
{
	*simple_cmd = malloc(sizeof(t_simple_cmd));
	if (*simple_cmd == NULL)
		return (2);
	(*simple_cmd)->cmd = NULL;
	(*simple_cmd)->args = NULL;
	(*simple_cmd)->next = NULL;
	(*simple_cmd)->infile = NULL;
	(*simple_cmd)->outfile = NULL;
	return (0);
}

int	add_args(t_args **args, char *value)
{
	while (*args != NULL)
		args = &(*args)->next;
	*args = malloc(sizeof(t_args));
	if (*args == NULL)
		return (2);
	(*args)->value = value;
	(*args)->next = NULL;
	return (0);
}

int	add_infiles(t_infiles **infile, char *file)
{
	while (*infile != NULL)
		infile = &(*infile)->next;
	*infile = malloc(sizeof(t_infiles));
	if (*infile == NULL)
		return (2);
	(*infile)->value = open(file, O_RDONLY);
	if ((*infile)->value == -1)
	{
		printf("open: %s\n", file);
	}
	(*infile)->next = NULL;
	return (0);
}

int	add_outfiles(t_outfiles **outfile , char *file, int mode)
{
	while (*outfile != NULL)
		outfile = &(*outfile)->next;
	*outfile = malloc(sizeof(t_outfiles));
	if (*outfile == NULL)
		return (2);
	if (mode == GREAT)
		(*outfile)->value = open(file, O_WRONLY | O_CREAT, S_IRWXU);
	else if (mode == DGREAT)
		(*outfile)->value = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if ((*outfile)->value == -1)
	{
		printf("open: %s\n", file);
	}
	(*outfile)->next = NULL;
	return (0);
}

int	parse_redir(t_simple_cmd *cmd)
{
	t_token			*token;
	int				last_op;

	token = &g_data.tokens;
	last_op = 0;
	while (token)
	{
		if ((token->type == LESS || token->type == DLESS 
				|| token->type == GREAT || token->type == DGREAT))
			last_op = token->type;
		if (token->type == REDIR)
		{
			//handle heredocs
			if (last_op == LESS)
				add_infiles(&(cmd->infile), token->value);
			else if(last_op == GREAT || last_op == DGREAT)
				add_outfiles(&(cmd->outfile), token->value, last_op);
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

	g_data.cmds = NULL;
	token = &g_data.tokens;
	init_cmd(&(g_data.cmds));
	simple_cmd = g_data.cmds;
	while (token)
	{
		while (token && token->type != PIPE)
		{
			if (token->type == WORD)
			{
				if (simple_cmd->cmd == NULL)
					simple_cmd->cmd = token->value;
				else
					add_args(&(simple_cmd->args), token->value);
			}	
			token = token->next;
		}
		if (!token)
			break ;
		parse_redir(simple_cmd);
		init_cmd(&(simple_cmd->next));
		simple_cmd = simple_cmd->next;
		token = token->next;
	}
	simple_cmd = g_data.cmds;
	while (simple_cmd)
	{
		// printf("%s %d %d\n", simple_cmd->cmd, simple_cmd->infile->value, simple_cmd->infile->value);
		printf("Args; %s\n", simple_cmd->cmd);
		break;
		simple_cmd = simple_cmd->next;
	}
	return (0);
}