#include "../include/minishell.h"

int	export(int argc, char **argv, char **envp)
{	
	char		**tmp;
	t_env_list *tmp_env;
	t_env_list *env_new;

	env_new = malloc(sizeof(t_env_list));
	tmp_env = env_new;
	while(*envp)
	{
		tmp = ft_split(*envp, '=');
		tmp_env->name = tmp[0];
		tmp_env->value = tmp[1];
		if (*(envp++ + 1) == NULL)
			tmp_env->next = NULL;
		else
			tmp_env->next = malloc(sizeof(t_env_list));
		tmp_env = tmp_env->next;
	}
	while (env_new != NULL)
	{
		printf("%s=\"%s\"\n", env_new->name, env_new->value);
		env_new = env_new->next;
	}
	return (0);
}
