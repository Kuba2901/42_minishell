/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aesthetics.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:00:05 by jnenczak          #+#    #+#             */
/*   Updated: 2025/02/15 15:42:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AESTHETICS_H
# define AESTHETICS_H

# include <mini_base.h>
# include <termios.h>
# include <fcntl.h>
# include <unistd.h>
# define HIDE_CURSOR "\033[?25l"
# define SHOW_CURSOR "\033[?25h"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define RESET   "\033[0m"
# define INTRO_SECONDS 10
# define SECOND_FROM_MICRO 1000000
# define SPINNER "-\\|/"

// void	show_intro(void);

#endif