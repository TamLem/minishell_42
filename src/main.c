/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:55 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/09 12:45:25 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_prompt()
{
	printf(KGRN);
	printf("$ ");
	printf(KNRM);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	
	g_data.env = envp;
	line = readline("$ ");
	if (line)
		lex(line);
	return (0);
	while(ft_strcmp(line, "exit") != 0)
	{
		printf("%s\n", line);
		line = readline(NULL);
	}
}