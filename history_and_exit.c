#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

// try to have ^C not shown!

void	sig_ctrlc(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

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

int	main(void)
{
	char	*line;

	line = NULL;
	signal(SIGINT, sig_ctrlc);
   	signal(SIGQUIT, SIG_IGN);
	while (!line || ft_strcmp(line, "exit") != 0)
	{
		line = readline(KGRN"$ "KNRM);
		if (line == NULL)
		{
			printf(KGRN"\033[A$ "KNRM);
			printf("exit\n");
			rl_replace_line("", 0);
			rl_redisplay();
			return (0);
		}
		if (line)
		{
			add_history(line);
			free(line);
		}
	}
}

// int	main2(void)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline(KGRN"$ "KNRM);
// 		if (line)
// 			add_history(line);
// 		if (!ft_strcmp(line, "exit"))
// 		{
// 			free(line);
// 			exit(0);
// 		}
// 		free(line);
// 	}
// }