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

int xecute(void)
{
	int init_stdin;
	int init_stdout;
	int cmd_len;
	int	i;
	t_simple_cmd *simple_cmd;

	
	init_stdin = dup(0);
	init_stdout = dup(1);
	simple_cmd = g_data.cmds;
	cmd_len = getcmdlen(simple_cmd);
	i = 0;
	while (i < cmd_len)
	{
		int	fdin;
		int	fdout;

		fdin = dup(0);
		fdout = dup(1);
		if (simple_cmd->infile->value != 0)
		i++;
	}
	printf("len %d\n", cmd_len);

	return (0);
}