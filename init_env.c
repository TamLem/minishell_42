#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_env_list
{
	char			*name;
	char			*value;
	struct s_env_list	*next;
}	t_env_list;

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

int	wcount(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	 return (count);
}

char	**wlen(const char *s, int wc, char c, char **s1)
{
	int	head;
	int	tail;
	int	i;

	tail = 0;
	head = 0;
	i = 0;
	while (i < wc)
	{
		while (s[head] == c && s[head])
			head++;
		tail = head;
		while (s[tail] && s[tail] != c)
			tail++;
		if (s[head] == '\0')
			break ;
		s1[i] = (char *)malloc(sizeof(char) * (tail - head + 1));
		ft_memcpy (s1[i], &((char *)s)[head], (tail - head));
		s1[i][tail - head] = '\0';
		i++;
		head = tail;
	}
	s1[i] = NULL;
	return (s1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		wc;

	if (s == 0)
		return (NULL);
	wc = wcount(s, c);
	arr = (char **)malloc((wc + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (wlen(s, wc, c, arr));
}


// void	init_env(int argc, char **argv, char **envp)
// {
// 	char **tmp;
// 	t_env_list *env_new;

// 	env_new = malloc(sizeof(t_env_list));
// 	while(*envp)
// 	{
// 		tmp = ft_split(*envp, '=');
// 		env_new->name = tmp[0];
// 		printf("%s\n", tmp[0]);
// 		env_new->value = tmp[1];
// 		printf("%s\n", tmp[1]);
// 		env_new->next = malloc(sizeof(t_env_list));
// 		env_new->next = env_new;
// 		envp++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{	
	char **tmp;
	t_env_list *tmp_env;
	t_env_list *env_new;

	env_new = malloc(sizeof(t_env_list));
	tmp_env = env_new;
	while(*envp)
	{
		tmp = ft_split(*envp, '=');
		tmp_env->name = tmp[0];
		tmp_env->value = tmp[1];
		if (envp++ == NULL)
			tmp_env->next = NULL;
		else
			tmp_env->next = malloc(sizeof(t_env_list));
		tmp_env = tmp_env->next;
	}
	while (env_new != NULL)
	{
		printf("%s=%s\n", env_new->name, env_new->value);
		env_new = env_new->next;
	}
	return (0);
}
