# include "minishell.h"

int	init_env(int argc, char **argv, char **envp)
{	
	char 		**split;
	t_env_list 	*tmp_env;

	g_data.env_list = ft_malloc(sizeof(t_env_list));
	if (!g_data.env_list)
		return(4);
	tmp_env =g_data.env_list;
	while(*envp)
	{
		split = ft_split(*envp, '=');
		tmp_env->name = split[0];
		tmp_env->value = split[1];
		tmp_env->is_env = true;
		tmp_env->next = ft_malloc(sizeof(t_env_list));
		if (!tmp_env->next)
			return (4);
		if (*(envp + 1) == NULL)
			tmp_env->next = NULL;
		else
			tmp_env = tmp_env->next;
		envp++;
	}
	return (0);
}

