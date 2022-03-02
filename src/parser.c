/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:08:11 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/02 22:27:37 by tlemma           ###   ########.fr       */
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

int	add_args(t_args **args, char *value)
{
	while (*args != NULL)
		args = &(*args)->next;
	*args = ft_malloc(sizeof(t_args));
	if (*args == NULL)
		return (2);
	(*args)->value = value;
	(*args)->next = NULL;
	return (0);
}

int	read_heredocs(char	*dlmtr)
{
	int			fd;
	char		*line;

	line = NULL;
	fd = open("heredocs", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	g_data.state = 2;
	line = readline("> ");
	if (g_data.state == 0)
	{
		close(fd);
		return (-1);
	}
	while (line && ft_strcmp(line, dlmtr))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	fd = open("heredocs", O_RDONLY);
	return (fd);
}

int	add_infiles(t_infiles **infile, char *file, int mode)
{
	while (*infile != NULL)
		infile = &(*infile)->next;
	*infile = ft_malloc(sizeof(t_infiles));
	if (*infile == NULL)
		return (2);
	if (mode == LESS)
	{
		(*infile)->value = open(file, O_RDONLY);
		if ((*infile)->value == -1)
			err_handle(0, file);
		(*infile)->dlmtr = NULL;
	}
	else if (mode == DLESS)
		(*infile)->value = read_heredocs(file);
	(*infile)->next = NULL;
	return (0);
}

int	add_outfiles(t_outfiles **outfile, char *file, int mode)
{
	while (*outfile != NULL)
		outfile = &(*outfile)->next;
	*outfile = ft_malloc(sizeof(t_outfiles));
	if (*outfile == NULL)
		return (2);
	if (mode == GREAT)
		(*outfile)->value = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else if (mode == DGREAT)
		(*outfile)->value = open(file, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	if ((*outfile)->value == -1)
		err_handle(0, file);

	(*outfile)->next = NULL;
	return (0);
}

int	parse_redir(t_simple_cmd *cmd, t_token *token)
{
	int				last_op;

	last_op = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == LESS || token->type == DLESS
				|| token->type == GREAT || token->type == DGREAT)
			last_op = token->type;
		if (token->type == REDIR)
		{
			if (last_op == LESS || last_op == DLESS)
				add_infiles(&(cmd->infile), token->value, last_op);
			else if (last_op == GREAT || last_op == DGREAT)
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
