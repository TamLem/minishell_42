/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:47:24 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/28 18:38:37 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int	ft_env(int argc, char *argv[], char *envp[])
{
	if (argc == 1)
	{
		print_env_or_export("env", NULL);
		return (0);
	}
	return (1);
}

char	*ft_getenv(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = ft_getenv_list(name);
	if (tmp_env)
		return (tmp_env->value);
	return (NULL);
}
