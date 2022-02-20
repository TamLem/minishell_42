/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/20 19:34:29 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	test()
{
	printf("%x\n", O_RDONLY);
	printf("%x\n", O_TRUNC);
	printf("%x\n", O_RDONLY | O_TRUNC);
	printf("%x\n", O_RDONLY | O_TRUNC | O_APPEND);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	
	// test();
	// return (0);
	g_data.env = envp;
	// line = "<<eof cat";
	line = readline(KGRN"$ "KNRM);
	while(line && ft_strcmp(ft_strtrim(line, " \t\n"), "exit") != 0)
	{
		if (line)
		{
			lex(line);
			parse();
			xecute();
		}
		free(line);
		line = readline(KGRN"$ "KNRM);
	}
	printf("logout\n");
	return (0);
}