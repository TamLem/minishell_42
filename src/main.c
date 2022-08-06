/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/11 17:08:12 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*line;
	char	*prompt;
	char	*cwd;
	char	*last;

	line = NULL;
	prompt = "$ ";
	cwd = getcwd(NULL, 0);
	last = ft_strrchr(cwd, '/');
	last++;
	prompt = ft_strjoin(last, prompt);
	free(cwd);
	line = readline(prompt);
	return (line);
}

int	end_session(void)
{
	change_ctrlc_sym(true);
	mem_free_all();
	rl_clear_history();
	printf("exit\n");
	return (g_data.exit_status);
}

int	refresh_session(int argc, char *argv[], char *envp[])
{
	g_data.env = envp;
	g_data.state = 0;
	g_data.tokens = NULL;
	g_data.cmds = NULL;
	g_data.n_heredocs = 0;
	return (0);
}

int	init_session(int argc, char *argv[], char *envp[])
{
	g_data.exit_status = 0;
	g_data.malloc_count = 0;
	g_data.mem_alloced = NULL;
	signal(SIGINT, sig_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	change_ctrlc_sym(false);
	init_env(argc, argv, envp);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	line = NULL;
	init_session(argc, argv, envp);
	while (true)
	{
		refresh_session(argc, argv, envp);
		line = prompt();
		if (line)
		{
			if (*line)
				add_history(line);
			if (lex(line) != 6 && !parse())
				xecute();
			g_data.state = 0;
		}
		else
			break ;
		free(line);
	}
	return (end_session());
}
