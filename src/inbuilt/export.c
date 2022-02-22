/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:32:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/17 21:22:25 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// set export attribute for shell variables
// marks each NAME for automatic export to the environment 
// of subsequently executed commands

// cases to handle:

// export								-> shows env alphabetically ordered from A to Z with "declare -x" in front
// export USER=Smth					-> changes USER to value "Smth"
// export USER=Smth HOME=SmthElse	 	-> changes USER to value "Smth" & HOME to "SmthElse"
// export USER=Smth USER=SmthElse	 	-> changes USER to value "SmthElse"
// // export $USER=Smth 	 				-> adds another path at the end with the last value of USER-> SmthElse="Smth" (or changes it if it does exist already)
// // export $USER=Smth USER=SmthNew		-> adds another path at the end with the last value of USER-> SmthElse="Smth" & changes the value of USER to USER=SmthNew

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*uc1;
	unsigned char	*uc2;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	if (*uc1 != *uc2)
		return (*uc1 - *uc2);
	while (*uc1 && *uc2)
	{
		if (*uc1 != *uc2)
			return (*uc1 - *uc2);
		uc1++;
		uc2++;
	}
	if (*uc1 == '\0' && *uc2 != '\0')
		return (0 - *uc2);
	else if (*uc2 == '\0' && *uc1 != '\0')
		return (*uc1);
	return (0);
}

void	order_env(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

// void	change_env(char **argv, char **env)
// {
// 	get the name with strcmp and change the value to the newly provided value
	
// }

// void	new_part(char **argv, char **env)
// {
// 	add with list_add_back a new segment to the list
// }

// int	ft_export(int argc, char **argv, char **env)
// {
// 	int	i;

// 	i = 1;
// 	if (argv[0] == "export")
// 	{
// 		order_env(env);
// 		while (env)
// 		{
// 			printf("declare -x %s", env);
// 		}
// 		while (argv[i] == "NAME=VALUE")
// 			change_env(argv[i], env);
// 		while (argv[i] != "NAME=VALUE")
// 			new_part(argv[i], env);
// 	}
// }


// PART 2

// typedef struct s_export
// {
// 	struct s_export	*key;
// 	struct s_export	*value;
// 	struct s_export	*next;
// }	t_export;


// int	export(int argc, char **argv, char **env)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	if (argc == 2 && argv == "export")
// 	{
// 		while (env)
// 		{
// 			printf("declare -x %s", env);
// 			env[i++];
// 		}
// 	}
// 	else
// 	{
// 		j = 0;
// 		while (argv[i] == "key=value" || argv[j] == "smth")
// 		{
// 			i = 0;
// 			while (env)
// 			{
// 				if (ft_strcmp(env[i]) == ft_stcmp(t_export.key))
// 				{
// 					delete value of env[i];
// 					add value of t_export to env[i];
// 				}
// 				env[i++];
// 			}
// 			j++;
// 		}
// 	}
// }

// PART WORKS

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**env;
// 	char	*oneenv;

// 	env = envp;
// 	order_env(env);
// 	while (*env)
// 	{
// 		oneenv = *env;
// 		printf("declare -x %s\n", oneenv);
// 		env++;
// 	}
// }

int	ft_export(int argc, char **argv, char **envp)
{
	t_env_list env_new;
	int i;

	if (argc == 1)
	{
		while (env_new != NULL)
		{
			printf("%s=\"%s\"\n", env_new->name, env_new->value);
			env_new = env_new->next;
		}
	}
	argv_tmp = malloc(sizeof(t_env_list));
	i = 2;
	if (argc > 1)
	{
		while (i < argc)
		{
			tmp_argv = ft_split(argv[i], '=');
			argv_tmp->name = tmp_argv[0];
			argv_tmp->value = tmp_argv[1];
			i++;
		}
		while (env_new != NULL)
		{
			if (argv_tmp->name == env_new->name)
			{
				env_new->value = argv_tmp->value;
				break ;
			}
			if (env_new->next == NULL)
				ft_lstadd_back(tmp_env, env_new);
		}
	}
}
