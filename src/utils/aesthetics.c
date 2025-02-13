/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aesthetics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:53:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/12 16:54:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <aesthetics.h>

static void	_show_logo(void)
{
	const char *ascii_logo[] = {
		RED    " ██████╗  ██████╗ ██╗     ███████╗██╗  ██╗ █████╗     " RESET BLUE "███╗   ███╗ █████╗ ██████╗  ██████╗ ███╗   ██╗███╗   ██╗ █████╗ " RESET,
		YELLOW " ██╔══██╗██╔═══██╗██║     ██╔════╝██║ ██╔╝██╔══██╗    " RESET GREEN "████╗ ████║██╔══██╗██╔══██╗██╔═══██╗████╗  ██║████╗  ██║██╔══██╗" RESET,
		CYAN   " ██████╔╝██║   ██║██║     ███████╗█████╔╝ ███████║    " RESET MAGENTA "██╔████╔██║███████║██║  ██║██║   ██║██╔██╗ ██║██╔██╗ ██║███████║" RESET,
		RED    " ██╔═══╝ ██║   ██║██║     ╚════██║██╔═██╗ ██╔══██║    " RESET BLUE "██║╚██╔╝██║██╔══██║██║  ██║██║   ██║██║╚██╗██║██║╚██╗██║██╔══██║" RESET,
		YELLOW " ██║     ╚██████╔╝███████╗███████║██║  ██╗██║  ██║    " RESET GREEN "██║ ╚═╝ ██║██║  ██║██████╔╝╚██████╔╝██║ ╚████║██║ ╚████║██║  ██║" RESET,
		CYAN   " ╚═╝      ╚═════╝ ╚══════╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝    " RESET MAGENTA "╚═╝     ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝  ╚═══╝╚═╝  ╚═╝" RESET,
		NULL
	};
	int	j;
	
	j = 0;
	printf(HIDE_CURSOR);
	printf("\n\n");
	while (ascii_logo[j] != NULL)
	{
		printf("         %s\n", ascii_logo[j]);
		usleep(SECOND_FROM_MICRO / 20);
		j++;
	}
}

void	show_intro(void)
{
	int	j;
	
	j = 0;
	printf("\033[2J\033[H");
	printf(HIDE_CURSOR);
	printf("\n\n");
	_show_logo();
	j = 0;
	while (j < 10)
	{
		printf("\r  " CYAN " Loading %c" RESET, SPINNER[j % 4]);
		fflush(stdout);
		usleep(SECOND_FROM_MICRO / 10);
		j++;
	}
	printf("\n\n" SHOW_CURSOR);
}