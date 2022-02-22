/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/22 20:14:51 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <signal.h>

void	test()
{
	printf("%x\n", O_RDONLY);
	printf("%x\n", O_TRUNC);
	printf("%x\n", O_RDONLY | O_TRUNC);
	printf("%x\n", O_RDONLY | O_TRUNC | O_APPEND);
}

void	sig_ctrlc(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// printf("es2 %d\n",g_data.exit_status);
	
	
	// g_data.rl_redisplay = 1;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	
	g_data.env = envp;
	g_data.exit_status = 0;
 	signal(SIGINT, sig_ctrlc);
	// signal(SIGINT, SIG_DFL);
   	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	// g_data.rl_redisplay = 0;
	while(ft_strcmp(ft_strtrim(line, " \t\n"), "exit") != 0)
	{
		// if (g_data.rl_redisplay)
		// {
		// 	line = readline(NULL);
		// 	g_data.rl_redisplay = 0;
		// }
		// else
		line = readline(KGRN"$ "KNRM);
		if (line)
		{
			add_history(line);
			lex(line);
			free(line);
			parse();
			xecute();
		}
		else
		{
			printf(KGRN"\033[A$ "KNRM);
			printf("exit\n");
			rl_replace_line("", 0);
			rl_redisplay();
			free(line);
			break ;
		}
		// free(line);
	}
	return (0);
}