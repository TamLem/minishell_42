/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:05 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/23 18:21:05 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env()
{
	t_env_list	*env_new;

	env_new = &g_data.env_list;
	while (env_new != NULL)
	{
		printf("%s=%s\n", env_new->name, env_new->value);
		env_new = env_new->next;
	}
}
