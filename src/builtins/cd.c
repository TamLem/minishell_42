/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/11 13:59:54 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "minishell.h"

void	change_dir(int dir, char *path, char *oldpath)
{
	dir = chdir(path);
	if (dir == -1)
	{
		err_handle(3, path);
		g_data.exit_status = 1;
	}
	else
		add_env("OLDPWD", ft_strdup(oldpath));
}

int	ft_cd(int argc, char **argv, char **envp)
{
	int			dir;
	char		*path;
	char		*oldpath;

	dir = 0;
	path = argv[1];
	oldpath = getcwd(NULL, 0);
	if (argc == 1)
		path = "~";
	if (ft_strcmp(path, "~") == 0)
		path = ft_getenv("HOME");
	if (ft_strcmp(path, "-") == 0)
	{
		path = ft_getenv("OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	if (path != NULL && *path)
		change_dir(dir, path, oldpath);
	free(oldpath);
	return (1);
}
