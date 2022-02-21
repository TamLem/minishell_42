/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell_ALL.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:27:17 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/17 20:20:02 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Allowed external Funtions:
readline
rl_clear_history
rl_on_new_line
rl_replace_line
rl_redisplay
add_history
printf
malloc
free
write
access
open
read
close
fork
wait
waitpid
wait3
wait4
signal
sigaction
sigemptyset
sigaddset
kill
exit -> useful for exit
getcwd -> useful for PWD
chdir -> useful for CD
stat
lstat
fstat
unlink
execve -> useful for 
dup
dup2
pipe
opendir
readdir
closedir
strerror
perror -> useful for error
isatty
ttyname
ttyslot
ioctl
getenv -> useful for env
tcsetattr
tcgetattr
tgetent
tgetflag
tgetnum
tgetstr
tgoto
tputs

Your shell should:
-> Display a prompt when waiting for a new command.
-> Have a working history.
-> Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
-> Not use more than one global variable. Think about it. You will have to explain its purpose.
-> Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
-> Handle '' (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
-> Handle "" (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign)
-> Implement redirections:
	-> < should redirect input.
	-> > should redirect output.
	-> << should be given a delimiter then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
	-> >> should redirect output in append mode.
-> Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
-> Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
-> Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
-> Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
-> In interactive mode:
	-> ctrl-C displays a new prompt on a new line.		on_key_press 3 stands for Ctrl+C
	-> ctrl-D exits the shell.							on_key_press 4 stands for Ctrl+D
	-> ctrl-\ does nothing.								on_key_press 28 stands for Ctrl+\
-> Your shell must implement the following builtins:
	-> echo with option -n
	-> cd with only a relative or absolute path
	-> pwd with no options
	-> export with no options
	-> unset with no options
	-> env with no options or arguments
	-> exit with no options
The readline() function can cause memory leaks. You don’t have to fix them. But that doesn’t mean your own code, yes the code you wrote, can have memory leaks.


/*====================INIT ENV====================*/

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

void	ft_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*tmp;

	tmp = *lst;
	if (new == NULL)
		return ;
	if (*lst == NULL || lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}


int	main(int argc, char **argv, char **envp)
{	
	char **tmp;
	char **tmp_argv;
	t_env_list *tmp_env;
	t_env_list *env_new;
	t_env_list *argv_tmp;

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
	if (ft_strcmp(argv) == "env" && argc == 2)
	{
		while (env_new != NULL)
		{
			printf("%s=%s\n", env_new->name, env_new->value);
			env_new = env_new->next;
		}
	}
	if (ft_strcmp(argv) == "export" && argc == 2)
	{
		while (env_new != NULL)
		{
			printf("%s=\"%s\"\n", env_new->name, env_new->value);
			env_new = env_new->next;
		}
	}
	argv_tmp = malloc(sizeof(t_env_list));
	if (ft_strcmp(argv[1]) == "export" && argc == 3)
	{
		tmp_argv = ft_split(argv[2], '=');
		argv_tmp->name = tmp_argv[0];
		argv_tmp->value = tmp_argv[1];
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
	return (0);
}
