/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:12:37 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/10 21:53:32 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

call the built in functions inside the execute function instead of forking a new process

int	execute(int argc, char **argv, char *env)
{
	if (argv[0] == "cd")
		ft_cd(argc, argv, env);
	else if (argv[0] == "echo")
		ft_echo(argc, argv, env);
	else if (argv[0] == "env")
		ft_env(argc, argv, env);
	else if (argv[0] == "exit")
		ft_exit(argc, argv, env);
	else if (argv[0] == "export")
		ft_export(argc, argv, env);
	else if (argv[0] == "pwd")
		ft_pwd(argc, argv, env);
	else if (argv[0] == "unset")
		ft_unset(argc, argv, env);
}
