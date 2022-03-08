/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:58:11 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/08 20:56:24 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

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

int	get_outfile(t_simple_cmd *simple_cmd,
	int stdout_init, int *fdout, int *fdin)
{
	int			fdpipe[2];
	t_outfiles	*outfile;

	outfile = simple_cmd->outfile;
	while (outfile && outfile->next)
		outfile = outfile->next;
	if (outfile)
		*fdout = outfile->value;
	else if (simple_cmd->next == NULL)
		*fdout = dup2(stdout_init, *fdout);
	if (simple_cmd->next != NULL)
	{
		if (pipe(fdpipe) == -1)
			return (4);
		*fdout = fdpipe[1];
		*fdin = fdpipe[0];
	}
	if (outfile != NULL)
		dup2(outfile->value, STDOUT_FILENO);
	else
		dup2(*fdout, STDOUT_FILENO);
	close(*fdout);
	return (0);
}

int	exec_cmd(t_simple_cmd *simple_cmd, int fd[4])
{
	int	ret;

	ret = 0;
	fd[IN] = get_infile(simple_cmd, fd[IN]);
	if (fd[IN] == -1 && close(fd[IN]) && close(fd[OUT]))
		return (2);
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	close(fd[OUT]);
	get_outfile(simple_cmd, fd[STDOUT_INIT], &fd[OUT], &fd[IN]);
	g_data.state = 1;
	if (is_builtin(simple_cmd->cmd))
		ret = exec_builtin(simple_cmd);
	else
	{
		ret = fork();
		if (ret == 0)
		{
			child_process(simple_cmd);
			exit(0);
		}
	}
	return (ret);
}

int	xecute(void)
{
	int				fd[4];
	t_simple_cmd	*simple_cmd;
	int				ret;

	ret = 0;
	simple_cmd = g_data.cmds;
	if (simple_cmd != NULL)
		init_fds(fd);
	else
		return (2);
	while (simple_cmd != NULL)
	{
		if (simple_cmd->error || !simple_cmd->cmd)
		{
			simple_cmd = simple_cmd->next;
			continue ;
		}
		ret = exec_cmd(simple_cmd, fd);
		if (ret == 2)
			return (2);
		simple_cmd = simple_cmd->next;
	}
	reset_fds(fd);
	waitpid(ret, &g_data.exit_status, 0);
	return (0);
}
