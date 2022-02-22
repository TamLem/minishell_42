/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:05 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/17 20:36:43 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**env;
// 	char	*oneenv;

// 	env = envp;
// 	while (*env)
// 	{
// 		oneenv = *env;
// 		printf("%s\n", oneenv);
// 		env++;
// 	}
// }

int	ft_env(int argc, char **argv, char **envp)
{
	t_env_list env_new;

	if (argc == 1)
	{
		while (env_new != NULL)
		{
			printf("%s=%s\n", env_new->name, env_new->value);
			env_new = env_new->next;
		}
	}
}
