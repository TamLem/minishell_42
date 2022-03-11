/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:22:28 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/11 15:44:17 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (err_handle(1, "pwd", path));
	printf("%s\n", path);
	free(path);
	return (0);
}
