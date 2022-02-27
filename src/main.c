/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/27 20:03:59 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	test()
{
	printf("%x\n", O_RDONLY);
	printf("%x\n", O_TRUNC);
	printf("%x\n", O_RDONLY | O_TRUNC);
	printf("%x\n", O_RDONLY | O_TRUNC | O_APPEND);
}

int	change_ctrlc_sym(bool	value)
{
	struct termios attr;

	tcgetattr(STDIN_FILENO, &attr);
	if (value == true)
	{
		attr.c_lflag |= ECHOCTL;
	}
	if (value == false)
	{
		attr.c_lflag &= ~ECHOCTL;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	return (0);
}

void	sig_ctrlc(int sig)
{
	if (g_data.state == 2)
	{
		close(STDIN_FILENO);
		// rl_replace_line("", 0);
		// if (g_data.state == 0)
		printf("\n");
	}
	else
	{
		if (g_data.state == 1)
			printf("^C");
		printf("\n");	
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (g_data.state == 0)
		rl_redisplay();
	g_data.state = 0;
}

int	ft_free()
{
	/* To Free */
	/* Env list */ 
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	
	g_data.env = envp;
	g_data.malloc_count = 0;
	g_data.mem_alloced = NULL;
	init_env(argc, argv, envp);
	g_data.exit_status = 0;
	change_ctrlc_sym(false);
 	signal(SIGINT, sig_ctrlc);
   	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	g_data.state = 0;
	while(true)
	{
		line = readline(KGRN"$ "KNRM);
		if (line)
		{
			if (ft_strcmp(ft_strtrim(line, " \t\n"), "exit") == 0)
				exit(0);
			if (*line)
				add_history(line);
			if(!lex(line))
			{
				parse();
				xecute();
			}
			g_data.state = 0;
		}
		else
			break ;
		free(line);
	}
	change_ctrlc_sym(true);
	mem_free_all();
	system("leaks minishell");
	return (0);
}