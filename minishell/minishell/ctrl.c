#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

// #define CTRL_C 0
// #define CTRL_D 1
// #define CTRL_BACKSLASH 130

void	sig_ctrlc(int sig)
{
    if (sig == SIGINT)
    {
		printf("hello\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
        exit(0);
    }
    if (sig == EOF)
    {
        printf("exit\n");
        exit(0);
    }
    // fprintf(stderr, "check\n");
}

void	sig_ctrld(int sig)
{
    if (sig == EOF)
    {
		printf("exit\n");
        exit(0);
    	// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
    }
}

int main(int argc, char **argv)
{
    int i;

    // // sigaction(sig, );
    signal(SIGINT, sig_ctrlc);
    signal(SIGQUIT, sig_ctrlc);

    while (1)
    {
        // if (SIGINT == CTRL_C)
        // {
        //     signal(SIGINT, sig_ctrlc);
        // }
        // if (SIGINT == CTRL_D)
        // {
            // signal(SIGINT, sig_ctrld);
        // }
        // if (SIGINT == CTRL_D)
        // {
        //     printf("%d\n", SIGINT);
        //     signal(SIGINT, sig_handletwo);
        //     printf("%d\n", SIGINT);
        //     // sig_handletwo(SIGINT);
        //     return (0);
        // }
        // if (SIGINT == CTRL_C)
        // {
        //     printf("%d\n", SIGINT);
        //     signal(SIGINT, sig_handle);
        //     printf("%d\n", SIGINT);
        //     // sig_handle(SIGINT);
        //     return (1);
        // }
    }
    // signal(SIGQUIT, SIG_IGN);
}

// signal
// sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);
// sigemptyset
// sigaddset