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
	t_infiles	*infile;
	t_outfiles	*outfile;

	fdin = dup(init_stdin);
	fdout = dup(init_stdout);
	printf("%d %d\n", fdin, fdout);
	ret = 0;
			int	fdpipe[2];
	while (simple_cmd != NULL)
	{
		infile = simple_cmd->infile;
		outfile = simple_cmd->outfile;
		while (infile && infile->next)
			infile = infile->next;
		if (infile)
			fdin = infile->value;
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
		dprintf(2, "fdin %d fdout %d\n", fdin, fdout);
		dup2(fdout, 1);
		close(fdout);
		ret = fork();
		if (ret == 0)
			child_process(&simple_cmd->cmd);
		else
			simple_cmd = simple_cmd->next;
		printf("PID %d\n", getpid());
	}
	close(init_stdin);
	close(init_stdout);
	waitpid(ret, NULL, 0);
	printf("len %d\n", cmd_len);

	return (0);
}