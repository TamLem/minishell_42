#include "../include/minishell.h"
#include "xecutor.h"

int	getcmdlen(t_simple_cmd *cmds)
{
	int	len;

	len = 0;
	while(cmds)
	{
		cmds = cmds->next;
		len++;
	}
	return (len);
}

int	child_process(char **cmd)
{
	char	**path;

	// exit(0);
	path = ft_getpath(g_data.env, *cmd);
	while (execve(*path, cmd, NULL) && *path)
			path++;
		
	return (0);
}

int	get_infile(t_simple_cmd *simple_cmd, int fdin)
{
	t_infiles	*infile;
	t_outfiles	*outfile;
	char		*line;
	int			fd;


	infile = simple_cmd->infile;
	outfile = simple_cmd->outfile;
	while (infile) //here
	{
		if (infile->value == 0)
		{
			fd = open("heredocs", O_WRONLY | O_CREAT, S_IRWXU);
			while (ft_strcmp((line = readline(NULL)), infile->dlmtr))
			{
				write(fd, line, sizeof(line));
			}
			infile->value = fd;
		}
		dprintf(2, "fdin %d\n", infile->value);
		if (infile->next)
			infile = infile->next;
	}
	if (infile)
		fdin = infile->value;
	return (fdin);
}

int xecute(void)
{
	int init_stdin;
	int init_stdout;
	int cmd_len;
	int	i;
	t_simple_cmd *simple_cmd;

	
	init_stdin = dup(STDERR_FILENO);
	init_stdout = dup(STDOUT_FILENO);
	simple_cmd = g_data.cmds;
	cmd_len = getcmdlen(simple_cmd);
	i = 0;
	int	fdin;
	int	fdout;
	int	ret;
	// t_infiles	*infile;
	t_outfiles	*outfile;

	fdin = dup(init_stdin);
	fdout = dup(init_stdout);
	printf("%d %d\n", fdin, fdout);
	ret = 0;
	int	fdpipe[2];
	while (simple_cmd != NULL)
	{
		fdin = get_infile(simple_cmd, fdin);
		// infile = simple_cmd->infile;
		outfile = simple_cmd->outfile;
		// while (infile && infile->next)
		// 	infile = infile->next;
		// if (infile)
		// 	fdin = infile->value;
		dprintf(2, "fdin %d fdout %d\n", fdin, fdout);
		dup2(fdin, 0);
		close(fdin);
		if (simple_cmd->next == NULL)
		{
			while (outfile && outfile->next)
				outfile = outfile->next;
			if (outfile)
				fdout = outfile->value;
			else
				fdout = dup(init_stdout);
		}
		else
		{
			if(pipe(fdpipe) == -1)
				return (4);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		ret = fork();
		if (ret == 0)
			child_process(&simple_cmd->cmd);
		else
			simple_cmd = simple_cmd->next;
	}
	close(init_stdin);
	close(init_stdout);
	waitpid(ret, NULL, 0);
	return (0);
}