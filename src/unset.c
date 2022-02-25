/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:09 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/25 19:06:03 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "minishell.h"

/* Check for invalid chars */

int	ft_unset(int argc, char *argv[], char *envp[])
{
    t_env_list  *tmp;
    t_env_list  *next;
    t_env_list  *tmp_env;
	
    tmp_env = g_data.env_list;
    if ((ft_strcmp(argv, tmp) == 0))
    {
        free(tmp_env->name);
        free(tmp_env->value);
        g_data.env_list = tmp_env->next;
        free(tmp_env);
    }
    while (tmp_env != NULL)
    {
        next = tmp_env->next;
        if (next != NULL && ((ft_strcmp(argv, next->name)) == 0))
        {
            tmp_env->next = next->next;
            free((next->name));
            free((next->value));
            free(next);
        }
        tmp_env = tmp_env->next;
    }
	return (0);
}