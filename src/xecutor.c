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
char	**init_args(t_simple_cmd *simple_cmd)
{
	int		i;
	int		len;
	char	**arg_array;
	t_args 	*args;

	i = 0;
	len = 0;
	args = simple_cmd->args;
	while(args && ++len)
		args = args->next;
	arg_array = malloc(sizeof(char *) * (len + 1));
	arg_array[len] = NULL;
	args = simple_cmd->args;
	while (i < len)
	{
		arg_array[i] = args->value;
		args = args->next;
		i++;
	}
	return (arg_array);
}

void	child_exit(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(130);
}

int	child_process(t_simple_cmd *simple_cmd)
{
	char	**path;
	char	**args;

   	signal(SIGINT, child_exit);
	if (!check_cmds(simple_cmd->cmd))
	{
		dprintf(2, "minishell: %s: command not found\n", simple_cmd->cmd);
		return (1);
	}
	path = ft_getpath(g_data.env, simple_cmd->cmd);
	args = init_args(simple_cmd);
	while (execve(*path, args, g_data.env) && *path)
			path++;
	free_dp(args);
	free_dp(path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (0);
}

int	get_infile(t_simple_cmd *simple_cmd, int fdin)
{
	int			fd;
	char		*line;
	t_infiles	*infile;

	infile = simple_cmd->infile;
	line = NULL;
	while (infile)
	{
		if (infile->value == 0)
		{
			fd = open("heredocs", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
			g_data.state = 2;
			line = readline("> ");
			if (g_data.state == 0)
			{
				close(fd);
				return (-1);
			}
			while (line && ft_strcmp(line, infile->dlmtr))
			{
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				free(line);
				line = readline("> ");
			}
			free(line);
			close(fd);
			fd = open("heredocs", O_RDONLY);
			infile->value = fd;
		}
		// dprintf(2, "fdin %d\n", infile->value);
		fdin = infile->value;
		infile = infile->next;
	}
	return (fdin);
}

int xecute(void)
{
	int				fdin;
	int				fdout;
	int				fdpipe[2];
	int				ret;
	int				init_stdin;
	int				init_stdout;
	int				cmd_len;
	t_simple_cmd	*simple_cmd;
	t_outfiles		*outfile;

	
	ret = 0;
	simple_cmd = g_data.cmds;
	if (simple_cmd != NULL)
	{
		init_stdin = dup(STDIN_FILENO);
		init_stdout = dup(STDOUT_FILENO);
		cmd_len = getcmdlen(simple_cmd);
		fdin = dup(init_stdin);
		fdout = dup(init_stdout);
	}
	else
		return (2);
	// printf("%d %d\n", fdin, fdout);
	while (simple_cmd != NULL)
	{
		close(fdin);
		fdin = get_infile(simple_cmd, fdin);
		if (fdin == -1)	
		{
			close(fdin);
			close(fdout);
			break ;
		}		/* maybe unsafe */
		outfile = simple_cmd->outfile;
		// dprintf(2, "fdin %d fdout %d\n", fdin, fdout);
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
		g_data.state = 1;
		ret = fork();
		if (ret == 0)
		{
			child_process(simple_cmd);
			exit(1);
		}
		else
			simple_cmd = simple_cmd->next;
	}
	dup2(init_stdin, STDIN_FILENO);
	dup2(init_stdout, STDOUT_FILENO);
	close(init_stdin);
	close(init_stdout);
	waitpid(ret, &g_data.exit_status, 0);
	// printf("es1 %d\n", g_data.exit_status);
	
	return (0);
}