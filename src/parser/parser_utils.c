/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:39:24 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/08 13:15:13 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

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
		{
			err_handle(3, file);
			return (3);
		}
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
	(*outfile)->next = NULL;
	return (0);
}

bool	is_io_modifier(int type)
{
	if (type == LESS || type == DLESS
		|| type == GREAT || type == DGREAT)
		return (true);
	return (false);
}
