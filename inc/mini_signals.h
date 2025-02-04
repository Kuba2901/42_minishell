#ifndef MINI_SIGNALS_H
# define MINI_SIGNALS_H

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

void	setup_signals(void);
void	handle_sigint(int sig);

# endif