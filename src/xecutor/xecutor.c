/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:58:11 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/11 12:44:02 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"
#include <signal.h>

int	get_infile(t_simple_cmd *simple_cmd, int fdin)
{
	char		*line;
	t_infiles	*infile;

	infile = simple_cmd->infile;
	line = NULL;
	while (infile)
	{
		close(fdin);
		fdin = infile->value;
		if (fdin == -1)
			return (-1);
		infile = infile->next;
	}
	return (fdin);
}

int	get_outfile(t_simple_cmd *simple_cmd, int fd[4], int order)
{
	int			fdpipe[2];
	t_outfiles	*outfile;

	outfile = simple_cmd->outfile;
	while (outfile && outfile->next)
		outfile = outfile->next;
	if (outfile)
		fd[OUT] = outfile->value;
	else if (simple_cmd->next == NULL)
		dup2(fd[STDOUT_INIT], fd[OUT]);
	if (simple_cmd->next != NULL)
	{
		if (pipe(fdpipe) == -1)
			return (4);
		fd[IN] = fdpipe[0];
		fd[OUT] = fdpipe[1];
	}
	if (outfile != NULL)
		dup2(outfile->value, STDOUT_FILENO);
	else
		dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
	return (0);
}

int	exec_cmd(t_simple_cmd *simple_cmd, int fd[4], int order)
{
	int	ret;

	ret = 0;
	fd[IN] = get_infile(simple_cmd, fd[IN]);
	if (fd[IN] == -1 && close(fd[IN]) && close(fd[OUT]))
		return (2);
	dup2(fd[IN], STDIN_FILENO);
	get_outfile(simple_cmd, fd, order);
	g_data.state = 1;
	if (is_builtin(simple_cmd->cmd))
		ret = exec_builtin(simple_cmd);
	else
	{
		ret = fork();
		if (ret == 0)
		{
			close(fd[IN]);
			child_process(simple_cmd);
		}
	}
	return (ret);
}

int	xecute(void)
{
	int				fd[4];
	t_simple_cmd	*simple_cmd;
	int				ret;
	int				i;

	ret = 0;
	i = 0;
	simple_cmd = g_data.cmds;
	if (simple_cmd != NULL)
		init_fds(fd);
	else
		return (2);
	while (simple_cmd != NULL && ++i)
	{
		if (!simple_cmd->error && simple_cmd->cmd)
			ret = exec_cmd(simple_cmd, fd, i);
		if (ret == 2)
			return (2);
		simple_cmd = simple_cmd->next;
	}
	reset_fds(fd);
	while (i--)
		wait(&g_data.exit_status);
	return (bashify_exit_status());
}
