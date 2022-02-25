/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/25 13:47:21 by tlemma           ###   ########.fr       */
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
	// init_env(argc, argv, envp);
	// ft_export();
	// return (0);
	g_data.exit_status = 0;
	change_ctrlc_sym(false);
 	signal(SIGINT, sig_ctrlc);
   	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	g_data.state = 0;
	while(ft_strcmp(ft_strtrim(line, " \t\n"), "exit") != 0)
	{
		line = readline(KGRN"$ "KNRM);
		if (line)
		{
			if (*line)
				add_history(line);
			if(!lex(line))
			{
				parse();
				xecute();
			}
			free(line);
			g_data.state = 0;
		}
		else
		{
			free(line);
			break ;
		}
		// free(line);
	}
	change_ctrlc_sym(true);
	return (0);
}