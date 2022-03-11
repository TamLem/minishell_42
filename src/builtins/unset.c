/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:09 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/11 15:44:39 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "minishell.h"

/* Check for invalid chars */

int	ft_unset(int argc, char *argv[], char *envp[])
{
	t_env_list	*next;
	t_env_list	*tmp_env;
	int			i;

	i = 1;
	tmp_env = g_data.env_list;
	while (argv[i])
	{
		if (!is_valid_name(argv[i]))
			err_handle(2, "unset", argv[i]);
		if ((ft_strcmp(argv[i], tmp_env->value) == 0))
			g_data.env_list = tmp_env->next;
		while (tmp_env != NULL)
		{
			next = tmp_env->next;
			if (next != NULL && ((ft_strcmp(argv[i], next->name)) == 0))
				tmp_env->next = next->next;
			tmp_env = tmp_env->next;
		}
		i++;
	}
	return (0);
}
