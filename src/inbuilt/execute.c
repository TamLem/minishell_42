/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:12:37 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/25 18:14:24 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	exec_builtin(int argc, char **argv, char *env)
{
	int	res;

	res = 0;
	if (ft_strcmp(argv[0], "cd") == 0)
		res = ft_cd(argc, argv, env);
	else if (ft_strcmp(argv[0], "echo") == 0)
		res = ft_echo(argc, argv, env);
	else if (ft_strcmp(argv[0], "env") == 0)
		res = ft_env(argc, argv, env);
	else if (ft_strcmp(argv[0], "export") == 0)
		res = ft_export(argc, argv, env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		res = ft_unset(argc, argv, env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		res = ft_pwd(argc, argv, env);
	else if (ft_strcmp(argv[0], "exit") == 0)
		res = ft_exit(argc, argv, env);
	return (res);
}
